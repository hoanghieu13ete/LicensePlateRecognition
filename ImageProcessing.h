#pragma once
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

// can bang anh mau
Mat Histogram(Mat input)
{
	Mat hsv, his;
	cvtColor(input, hsv, CV_BGR2HSV);
	vector<Mat>hsv_channels;
	split(hsv, hsv_channels);	// tach lam 3 kenh mau
	equalizeHist(hsv_channels[2], hsv_channels[2]);	// can bang his kenh mau (2): value
	merge(hsv_channels, hsv);	// tron mau 
	cvtColor(hsv, his, CV_HSV2BGR);
	return his;
}
// tang giam do sang tu dong cho tung anh
Mat Brightness(Mat input)
{
	Mat tangdosang;
	tangdosang = input.clone();
	double alpha, beta;
	double minVal, maxVal;
	minMaxLoc(input, &minVal, &maxVal); // tim CDS toi thieu va toi da
	alpha = 255.0 / (maxVal - minVal);	// dieu chinh do sang
	beta = -minVal * 255.0 / (maxVal - minVal); // dieu chinh do tuong phan
	input.convertTo(tangdosang, CV_8U, alpha, beta);
	return tangdosang;
}
// cat anh theo kich thuoc nhap tu ban phim
Mat CutImg(Mat input)
{
	cout << "Nhap vtri1, vtri2, chieu dai va chieu rong. \n";
	int vtri1, vtri2, chieurong, chieudai; // dua vao vtri va kich thuoc can cat
	cin >> vtri1>> vtri2 >> chieurong >> chieudai;
	cout << endl;
	Rect r = Rect(vtri1, vtri2, chieurong, chieudai);
	rectangle(input, r, CV_RGB(255, 0, 255), 5, 4); // ve hinh chu nhat vao anh 
	Mat a(input, r);	// cat phan hinh chu nhat da ve
	return a;
}
