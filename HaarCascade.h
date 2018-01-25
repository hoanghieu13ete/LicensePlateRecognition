#pragma once
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace cv;

class HaarCascade
{
public:
	bool LoadXML();
	Mat DectectLicensePlate(Mat image);
	vector<Mat> DetectNumber(Mat image);
private:
	CascadeClassifier myDetect;
};