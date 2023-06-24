#pragma once
#include <iostream>
#include <complex>
#include <cstdlib>
#include <ctime>

#include "header_includes.hpp"


class GaussianRandomField {
public:
    GaussianRandomField(std::size_t size, int alpha)
                     : size(size), alpha(alpha) {
        xt::random::seed(time(NULL));
        translate = (size + 1) / 2;
    }

    void generate_grid(){
        auto grid = xt::meshgrid(xt::arange<double>(0, this->size),
                                 xt::arange<double>(0, this->size));

        xt::xarray<double> x = std::get<0>(grid) - translate;
        xt::xarray<double> y = std::get<1>(grid) - translate;

        this->xy_ = xt::stack(xt::xtuple(x, y));
        this->fftshift_roll(this->xy_);
    }

    void compute(){     
        auto amplitude = xt::pow(xt::sum(xt::square(this->xy_), 0) + 1e-10, -alpha);
        // std::cout << xt::pow((xt::sum(xt::square(p),0) + 1e-10), -alpha/4) << std::endl;        
        auto modified_amplitude = xt::xarray<double>(amplitude.shape());
        xt::noalias(modified_amplitude) = amplitude;
        xt::view(modified_amplitude, 0, 0) = 0;


        auto rn = xt::random::randn<double>({size, size});
        auto im = xt::random::randn<double>({size, size});

        xt::xarray<std::complex<double>> noise = xt::cast<std::complex<double>>(rn) +
                                                 xt::cast<std::complex<double>>(im) * std::complex<double>(0.0, 1.0);
        xt::xarray<std::complex<double>> mat_ifft2 = noise * modified_amplitude;

        auto gfield_imag = xt::fftw::ifft2(mat_ifft2);
        auto gfield = xt::real(gfield_imag);
        xt::dump_npy("gfield.npy", gfield);
    }

    // void save_to_npy(){
    //     xt::dump_npy("gfield.npy", this->gfield);
    // }

    // auto get_grf(){
    //     return this->gfield;
    // }

    void fftshift_roll(xt::xarray<double>& array) {
        std::size_t ndims = array.dimension();
        std::vector<std::ptrdiff_t> shift_indices(ndims);

        for (std::size_t i = 0; i < ndims; ++i) {
            std::ptrdiff_t shift = static_cast<std::ptrdiff_t>(array.shape(i)) / 2;
            shift_indices[i] = shift;
        }

        for (std::size_t i = 0; i < ndims; ++i) {
            auto rolled = xt::roll(array, shift_indices[i], i);
            array = xt::view(rolled, xt::all(), xt::all());
        }
    }

private:
    std::size_t size;
    int alpha;
    xt::xarray<double> xy_;
    // xt::xarray<std::complex<double>> gfield;
    int translate;
};
