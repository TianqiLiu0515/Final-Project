#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

Mat addBlur(){
    Mat img = imread("generated_inputs/Copy.jpg");
    Mat bimg;
    blur(img, bimg, Size(10, 10), Point(-1, -1), 4); // src, dst
    imwrite("generated_inputs/Copy.jpg", bimg);
}

int main() {
    addBlur();
}