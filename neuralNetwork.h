#pragma once
#include <iostream>
#include <string.h>
#include <opencv2/ml.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/objdetect.hpp"

using namespace cv::ml;
using namespace cv;
using namespace std;

class neuralNetwork {
public:
	void training();
	vector<string> testing(vector<Mat> &testMat);
};
