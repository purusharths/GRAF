## GRAF++: Gaussian RAndom Fields in c++

A header only library for generating Gaussian Random Fields. 

Requirements:
  1. FFTW3 <br>
  2. xtensor (header only)<br>
  3. xtensor-fftw (header only) <br>

This library is built on top of xtensor arrays. xtensor-fftw in turn calls xtensor. Since submodules are already added in the repository, only fftw3 has to be installed explicitly. The implementation is a bit slow, as of now the focus is not on performance but instead integration with [hiflow3](https://emcl-gitlab.iwr.uni-heidelberg.de/hiflow3.org/hiflow3/-/wikis/home).

### Usage
```
cd src
g++ -o demo demo.cc -l fftw3
./demo
```


![size=125, alpha=5](test/img/grf.png)

Values of alpha and size can be changed inside the demo.cc

##### @TODO:
    - Generate RF for mesh
    - Makefile
    - ini file
    - Add 2D Matern Covaraince function, Cholesky Factorization, and function for KL Decomposition
    - Fix `fftshift` loop for performance.