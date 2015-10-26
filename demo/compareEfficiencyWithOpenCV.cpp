#include <iostream>
#include "opencv2/opencv.hpp"
#include "../fastMorphMatWrapper.hpp"
#include <time.h>

#define TIME_CODE(ELAPSED, Code) \
{\
	clock_t __t1 = clock();/* complex name to avoid duplication*/\
	Code \
	clock_t __t2 = clock();\
	ELAPSED = (__t2 - __t1) * 1.0 / CLOCKS_PER_SEC;\
}

using namespace std;
using namespace cv;

void compare8UErode(Mat& img, Mat& kernel)
{
    cout << "=========================================================" << endl;
    cout << "Image(CV_8U) size: " << img.size() << endl;
    cout << "Kernel size:       " << kernel.size() << endl;

    Mat dst;
    double elapsed_time;
    TIME_CODE(elapsed_time,
            erode(img, dst, kernel);
            )
    cout << "elapsed time of OpenCV erode: " << elapsed_time << " secs" << endl;

    MatWrapper<uint8_t> img_w(img.rows, img.cols, img.data);
    MatWrapper<uint8_t> kernel_w(kernel.rows, kernel.cols, kernel.data);

    MatWrapper<uint8_t> dst_w;
    TIME_CODE(elapsed_time,
            hgwErode(img_w, dst_w, kernel_w);
            )
    cout << "elapsed time of HGW erode:    " << elapsed_time << " secs" << endl;

    Mat dst_w_cv(img.rows, img.cols, img.type(), dst_w.data);
    Mat errp = dst_w_cv - dst; // always > 0
    Mat errn = dst - dst_w_cv;
    cout << "Result error  estimation: " << sum(errp + errn)[0] << endl;
}

void compare8UDilate(Mat& img, Mat& kernel)
{
    cout << "=========================================================" << endl;
    cout << "Image(CV_8U) size: " << img.size() << endl;
    cout << "Kernel size:       " << kernel.size() << endl;

    Mat dst;
    double elapsed_time;
    TIME_CODE(elapsed_time,
            dilate(img, dst, kernel);
            )
    cout << "elapsed time of OpenCV dilate: " << elapsed_time << " secs" << endl;

    MatWrapper<uint8_t> img_w(img.rows, img.cols, img.data);
    MatWrapper<uint8_t> kernel_w(kernel.rows, kernel.cols, kernel.data);

    MatWrapper<uint8_t> dst_w;
    TIME_CODE(elapsed_time,
            hgwDilate(img_w, dst_w, kernel_w);
            )
    cout << "elapsed time of HGW dilate:    " << elapsed_time << " secs" << endl;

    Mat dst_w_cv(img.rows, img.cols, img.type(), dst_w.data);
    Mat errp = dst_w_cv - dst;
    Mat errn = dst - dst_w_cv;
    cout << "Result error  estimation: " << sum(abs(errp + errn))[0] << endl;
}

void compare16UErode(Mat& img, Mat& kernel)
{
    cout << "=========================================================" << endl;
    cout << "Image(CV_16U) size: " << img.size() << endl;
    cout << "Kernel size:        " << kernel.size() << endl;

    Mat dst;
    double elapsed_time;
    TIME_CODE(elapsed_time,
            erode(img, dst, kernel);
            )
    cout << "elapsed time of OpenCV erode: " << elapsed_time << " secs" << endl;

    MatWrapper<uint16_t> img_w(img.rows, img.cols, img.data);
    MatWrapper<uint16_t> kernel_w(kernel.rows, kernel.cols, kernel.data);

    MatWrapper<uint16_t> dst_w;
    TIME_CODE(elapsed_time,
            hgwErode(img_w, dst_w, kernel_w);
            )
    cout << "elapsed time of HGW erode:    " << elapsed_time << " secs" << endl;

    Mat dst_w_cv(img.rows, img.cols, img.type(), dst_w.data);
    Mat errp = dst_w_cv - dst;
    Mat errn = dst - dst_w_cv;
    cout << "Result error  estimation: " << sum(abs(errp + errn))[0] << endl;
}

void compare16UDilate(Mat& img, Mat& kernel)
{
    cout << "=========================================================" << endl;
    cout << "Image(CV_16U) size: " << img.size() << endl;
    cout << "Kernel size:        " << kernel.size() << endl;

    Mat dst;
    double elapsed_time;
    TIME_CODE(elapsed_time,
            dilate(img, dst, kernel);
            )
    cout << "elapsed time of OpenCV dilate: " << elapsed_time << " secs" << endl;

    MatWrapper<uint16_t> img_w(img.rows, img.cols, img.data);
    MatWrapper<uint16_t> kernel_w(kernel.rows, kernel.cols, kernel.data);

    MatWrapper<uint16_t> dst_w;
    TIME_CODE(elapsed_time,
            hgwDilate(img_w, dst_w, kernel_w);
            )
    cout << "elapsed time of HGW dilate:    " << elapsed_time << " secs" << endl;

    Mat dst_w_cv(img.rows, img.cols, img.type(), dst_w.data);
    Mat errp = dst_w_cv - dst;
    Mat errn = dst - dst_w_cv;
    cout << "Result error  estimation: " << sum(abs(errp + errn))[0] << endl;
}

int main(int argc, char* argv[])
{
    cout << "USAGE: " << argv[0] << " <INPUT.png>" << endl;
    cout << " compare efficiency with OpenCV based on INPUT.png" << endl;
    if (argc < 2) exit(-1);

    Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    Mat kernel2 = Mat::ones(19, 19, CV_8U);
    compare8UErode(img, kernel1);
    compare8UErode(img, kernel2);
    compare8UDilate(img, kernel1);
    compare8UDilate(img, kernel2);

    img.convertTo(img, CV_16U);
    kernel1 = Mat::ones(3, 3, CV_16U);
    kernel2 = Mat::ones(19, 19, CV_16U);
    compare16UErode(img, kernel1);
    compare16UErode(img, kernel2);
    compare16UDilate(img, kernel1);
    compare16UDilate(img, kernel2);
    return 0;
}
