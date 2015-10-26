# Herk-Gil-Werman(HGW) fast algorithm for morphology 

This repository does **NOT** depend on external libraries. However, in order to 
run the demo, you need to have OpenCV (tested on version 2.4.8) installed. To 
build the demo, just run

    ./buildDemo.py


`matWrapper.hpp` defines a template `MatWrapper`, which serves as a light 
alternative of OpenCV `Mat`. The usage is demonstrated in the demos.

## Demo

* `compareEfficiencyWithOpenCV`
* `erodeImage`

## Directories

* `data`: test images
* `demo`: demo source code

## Efficiency comparison with OpenCV

The following result is tested on 1.4 GHz Intel Core i5, with 4GB RAM and Mac OSX.
Note that:

1. OpenCV uses SIMD, so it's very fast
1. Due to the fact that SIMD functions can only process a fixed number of 
bytes in parallel, efficiency of OpenCV implementation decreases as we 
process 16Bit images of the same size
1. Pixel depth has little effect on HGW implementation


    =========================================================
    Image(CV_8U) size: [5472 x 3648]
    Kernel size:       [3 x 3]
    elapsed time of OpenCV erode: 0.021483 secs
    elapsed time of HGW erode:    0.699951 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_8U) size: [5472 x 3648]
    Kernel size:       [19 x 19]
    elapsed time of OpenCV erode: 0.02735 secs
    elapsed time of HGW erode:    0.576092 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_8U) size: [5472 x 3648]
    Kernel size:       [3 x 3]
    elapsed time of OpenCV dilate: 0.008891 secs
    elapsed time of HGW dilate:    0.610029 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_8U) size: [5472 x 3648]
    Kernel size:       [19 x 19]
    elapsed time of OpenCV dilate: 0.022744 secs
    elapsed time of HGW dilate:    0.578881 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_16U) size: [5472 x 3648]
    Kernel size:        [3 x 3]
    elapsed time of OpenCV erode: 0.049 secs
    elapsed time of HGW erode:    0.437014 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_8U) size: [5472 x 3648]
    Kernel size:       [19 x 19]
    elapsed time of OpenCV erode: 0.02735 secs
    elapsed time of HGW erode:    0.576092 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_8U) size: [5472 x 3648]
    Kernel size:       [3 x 3]
    elapsed time of OpenCV dilate: 0.008891 secs
    elapsed time of HGW dilate:    0.610029 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_8U) size: [5472 x 3648]
    Kernel size:       [19 x 19]
    elapsed time of OpenCV dilate: 0.022744 secs
    elapsed time of HGW dilate:    0.578881 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_16U) size: [5472 x 3648]
    Kernel size:        [3 x 3]
    elapsed time of OpenCV erode: 0.049 secs
    elapsed time of HGW erode:    0.437014 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_16U) size: [5472 x 3648]
    Kernel size:        [19 x 19]
    elapsed time of OpenCV erode: 0.058585 secs
    elapsed time of HGW erode:    0.367326 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_16U) size: [5472 x 3648]
    Kernel size:        [3 x 3]
    elapsed time of OpenCV dilate: 0.017879 secs
    elapsed time of HGW dilate:    0.313497 secs
    Result error  estimation: 0
    =========================================================
    Image(CV_16U) size: [5472 x 3648]
    Kernel size:        [19 x 19]
    elapsed time of OpenCV dilate: 0.101644 secs
    elapsed time of HGW dilate:    0.453101 secs
    Result error  estimation: 0
