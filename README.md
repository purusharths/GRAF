## Gaussian Random Field

A header only library for generating Gaussian Random Fields. 

Requirements: <br>
  1. FFTW3 <br>
  2. xtensor <br>
  3. xtensor-fftw <br>

This library is built on top of xtensor arrays. The implementation is a bit slow, as of now the focus is not on performance but instead integration with [hiflow3](https://emcl-gitlab.iwr.uni-heidelberg.de/hiflow3.org/hiflow3/-/wikis/home).

### Usage
```
cd src
g++ -o demo demo.cc -l fftw3
./demo
```

Values of alpha and size can be changed inside the demo.cc

##### @TODO:
    - Generate RF for mesh
    - Makefile
    - ini file
    - Add 2D Matern Covaraince function, Cholesky Factorization, and function for KL Decomposition
    - Fix `fftshift` loop for performance.