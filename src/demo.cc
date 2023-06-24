#include <iostream>

#include "../include/graf.h"


int main(){

    GaussianRandomField grf(125, 5);
    grf.generate_grid();
    grf.compute();
    // grf.save_to_npy();

}