#pragma once
#include <iostream>
#include <complex>
#include <cstdlib>
#include <ctime>

#include "header_includes.hpp"


class GaussianRandomField {
public:
    FFTShiftGenerator(std::size_t size, std::size_t alpha)
                     : size(size), alpha(alpha) {
        xt::random::seed(time(NULL));
        translate = (size + 1) / 2;
    }

    void generate(){
        auto grid = xt::meshgrid(xt::arange<double>(0, this->size),
                                 xt::arange<double>(0, this->size));

        xt::xarray<double> x = std::get<0>(grid) - translate;
        xt::xarray<double> y = std::get<1>(grid) - translate;

        this->xy_ = xt::stack(xt::xtuple(x, y));

        this->fftshift_roll(this->xy_);
    }

    void compute(){
        auto amplitude = xt::pow(xt::sum(xt::square(p), 0) + 1e-10, -alpha / 4);
    }

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
    std::size_t size, p;
    xt::xarray<double> xy_;
    int translate;
