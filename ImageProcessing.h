#pragma once
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;
using namespace cv;

class ProcessImg
{
	public:
		Mat ProImg(Mat &input);
		Mat Color(Mat &input);
		Mat Dilate(Mat &input);
		Mat CutImg(Mat &input, int vtri1, int vtri2, int dai, int rong);
		Mat FindObject(Mat &input);
	private:
		int vti1, vtri2, dai, rong;
};


