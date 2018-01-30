#pragma once
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

class ProcessImgTest
{
	public:
		Mat ProcessImg(Mat input);
		Mat Color(Mat input);

};


