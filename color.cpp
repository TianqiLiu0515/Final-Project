#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>
using namespace std;
using namespace cv;


void monoColor(){
    Mat img = imread("generated_inputs/Copy.jpg");
    // Mat img = imread("/Users/tianqi/Desktop/drive.jpg");
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            int avg = (img.at<Vec3b>(row, col)[0] + img.at<Vec3b>(row, col)[1] +
                       img.at<Vec3b>(row, col)[2]) / 3;

            if (avg > 100){
                img.at<Vec3b>(row, col) = Vec3b(0.3 * img.at<Vec3b>(row, col)[0],
                                                 0.6 * img.at<Vec3b>(row, col)[1],
                                                 1 * img.at<Vec3b>(row, col)[2]);
            }
            else {
                img.at<Vec3b>(row, col) = Vec3b(0.1 * img.at<Vec3b>(row, col)[0],
                                                 0.4 * img.at<Vec3b>(row, col)[1],
                                                 0.8 * img.at<Vec3b>(row, col)[2]);
            }
        }
    }
    imwrite("generated_inputs/Copy.jpg", img);
    // imwrite("/Users/tianqi/Desktop/result.jpg", img);
}

int main() {
    monoColor();
}