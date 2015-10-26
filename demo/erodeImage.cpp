#include <iostream>
#include "opencv2/opencv.hpp"
#include "../fastMorphMatWrapper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    cout << "USAGE: " << argv[0] << " <INPUT.png>" << endl;
    cout << " erode INPUT.png" << endl;
    if (argc < 2) exit(-1);

    Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat kernel = Mat::ones(5, 5, CV_8U);

    MatWrapper<uint8_t> img_w(img.rows, img.cols, img.data);
    MatWrapper<uint8_t> kernel_w(kernel.rows, kernel.cols, kernel.data);
    MatWrapper<uint8_t> dst_w;
    hgwErode(img_w, dst_w, kernel_w);
    Mat dst(img.rows, img.cols, img.type(), dst_w.data);

    namedWindow("a");
    imshow("a", dst);
    waitKey(0);

    return 0;
}
