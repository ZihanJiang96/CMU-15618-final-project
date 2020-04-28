# OptiX version Ray Tracing

Developed and tested on GHC machine with

* CUDA v10.2
* Optix v6.5
* NVIDIA GeForce RTX 2080, driver version 440.82

This code is based on this git repo [weeker_raytracer](https://github.com/idcrook/weeker_raytracer)

## OptiX install

The Optix 6.5 SDK is installed at
`/afs/andrew.cmu.edu/usr19/zihanj/private/15618/NVIDIA-OptiX-SDK-6.5.0-linux64`

How to install:

First download and execute the install script from NVIDIA official website, then

``` bash
cd SDK/
cmake .
make
```

## Build

First update the OptiX installation path in `src/CMakeLists.txt`, then

``` bash
mkdir build
cd build
make
```

## Run

example:

``` bash
./restOfLifeOptix > image.ppm
```

Advanced example with additional command line parameters
`./restOfLifeOptix -v -s 0 -dx 1120 -dy 1120 -ns 1024 > image.ppm`

output

```bash
INFO: Display driver version: 440.82
INFO: OptiX RTX execution mode is ON.
INFO: Output image dimensions: 1120x1120
INFO: Number of rays sent per pixel: 1024
INFO: Scene number selected: 0
INFO: Scene description: Cornell box
INFO: Took 19.049 seconds.
```

In this example

* `-v` sets verbose output
* `-s 0` selects scene zero
* `-dx 1120 -dy 1120` sets image to be of width and height 1120x1120
* `-ns 1024` collect 1024 sampled rays per pixel
