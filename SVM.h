//// chay ham training de train mo hinh (can tap co so du lieu)
/// chay ham testing de du doan, input can dinh danh: vector<Mat>, moi Mat co kich thuoc 12x24

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

class SVMModel {
public:
	
	void training();
	Mat testing(vector<Mat> &testCells);
}; 
