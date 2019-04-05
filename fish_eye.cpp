#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>
using namespace std;
using namespace cv;


void myFisheye(){
    // Mat img = imread("generated_inputs/Copy.jpg");
    Mat img = imread("/Users/tianqi/Desktop/drive.jpg");
    int tx = (img.cols / 3) + rand() % 20 + 1;
    int ty = (img.rows / 1.6) + rand() % 20 + 1;

    int range = 50;

    for (int row = tx - range; row < tx +range; row++)
    {
        for (int col = ty - range; col < ty + range; col++)
        {
            int dist = sqrt(pow(row - tx,2) + pow(col - ty,2));
            if (dist < 50){
                img.at<Vec3b>(row, col) = img.at<Vec3b>(row + dist *(tx - row) / 150, col + dist * (tx - row) / 150);
            }
        }
    }
    // imwrite("generated_inputs/Copy.jpg", img);
    imwrite("/Users/tianqi/Desktop/result.jpg", img);
}


int main() {
    myFisheye();
}