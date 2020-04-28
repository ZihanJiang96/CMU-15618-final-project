# OptiX version Ray Tracing

Developed and tested on GHC machine with

* CUDA v10.2
* Optix v6.5
* NVIDIA GeForce RTX 2080, driver version 440.82

This code is based on this git repo [weeker_raytracer](https://github.com/idcrook/weeker_raytracer)

## OptiX install

The Optix 6.5 SDK is installed at

``` bash
/afs/andrew.cmu.edu/usr19/zihanj/private/15618/NVIDIA-OptiX-SDK-6.5.0-linux64
```

How to install:

First download and execute the install script from NVIDIA official website, then

``` bash
cd SDK/
cmake .
make
```

## Build

