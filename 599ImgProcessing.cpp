/*
Project: Test the safty of self-driving car
course: EE599 
auther: Bixiong Xiang
method we used:
	composition
	inheritance
	virtual function
	pure virtual function
	initialization
	inline functions
	shallow copy
	deep copy
	multi-dimentional array
	STL(set)
	multi-dimentional array
	C++ reference.
	condition directives & debug mode
	function pointer
	friend
*/
#include "stdafx.h"

#ifndef Img_Process 
#define Img_Process

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2\imgproc\types_c.h>
#include <set>

#endif

//debug mode
#define DEBUG

using namespace std;
using namespace cv;


class ImgProcessorAPI{
public:
	//file io
	bool virtual load(string path) = 0;
	void virtual write(string path) = 0;
	
	//img prosassing
	void virtual imgProcessing(string method) = 0;
};

class ImgProcessor : public ImgProcessorAPI{
public:
	Mat img;
	set<string> methods; // store the valid methods

	friend ImgConverter;

	ImgProcessor(){
		methods.insert("color");
		methods.insert("fisheye");

	}

	//file io
	bool virtual load(string fpath){
		this->img = imread(fpath);

		return true;
	}

	void virtual write(string fpath){
		imwrite(fpath, img);
	}

	//img prosassing
	void imgProcessing(string method){
		if (!isValidMethod(method)){
#ifdef DEBUG
			printf("Input method not support!\n");
#endif // DEBUG
			return;
		}
		if (method == "color"){
			monoColor();
		} else if (method == "fisheye"){
			myFisheye();
		}
	}

	inline bool isValidMethod(string m){
		return methods.find(m) != methods.end();
	}

	//overload imgProcessing, allow other method as a function input
	void imgProcessing(void (*fptr)()){
		fptr();
	}

	//process function

	//color
	void monoColor(){
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

	}

	//fish eye
	void myFisheye(){
		int tx = (img.cols / 3) + rand() % 20 + 1;
		int ty = (img.rows / 1.6) + rand() % 20 + 1;

		int range = 50;

		for (int row = tx - range; row < tx + range; row++)
		{
			for (int col = ty - range; col < ty + range; col++)
			{
				int dist = sqrt(pow(row - tx, 2) + pow(col - ty, 2));
				if (dist < 50){
					img.at<Vec3b>(row, col) = img.at<Vec3b>(row + dist *(tx - row) / 150, col + dist * (tx - row) / 150);
				}
			}
		}
	}


};

class ImgConverter{ // friend of processor so can convert a img

	void toBlackWite(Mat * img){
		cvtColor(*img, *img, CV_BGR2GRAY); // src dst para
	}
};

//void demoImgProcess(){
//	printf("demoImgProcess");
//}

int main(int argc, char* argv[])
{
#ifdef DEBUG
	printf("Debug mode:\n");
#endif // DEBUG
	string method = argv[1];

	string defaultPath = "generated_inputs/Copy.jpg";

	string &path = defaultPath;

	ImgProcessor processor;
#ifdef DEBUG
	printf("Object created!\n");
#endif // DEBUG

	processor.load(path);
#ifdef DEBUG
	printf("Image loaded\nStart image processing...\n");
#endif // DEBUG

	//void(*fptr)() = demoImgProcess;
	//processor.imgProcessing(fptr);

	processor.imgProcessing(method);
#ifdef DEBUG
	printf("Image processed\n");
#endif // DEBUG

	processor.write(path);
#ifdef DEBUG
	printf("Image saved!\n");
#endif // DEBUG

	return 0;
}




