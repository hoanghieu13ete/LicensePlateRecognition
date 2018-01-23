#pragma once
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

CascadeClassifier myDetect;
Mat CanBangAnhMau(Mat A)
{
	Mat hsv, his;
	cvtColor(A, hsv, CV_BGR2HSV);
	vector<Mat>hsv_channels;
	split(hsv, hsv_channels);	// tach lam 3 kenh mau
	equalizeHist(hsv_channels[2], hsv_channels[2]);	// can bang his kenh mau (2): value
	merge(hsv_channels, hsv);	// tron mau 
	cvtColor(hsv, his, CV_HSV2BGR);
	return his;
}
Mat TangDoSang(Mat A)
{
	Mat tangdosang;
	tangdosang = A.clone();
	double alpha = 1;
	int beta = 2.5;
	for (int i = 0;i < A.rows;i++)
	{
		for (int j = 0;j < A.cols;j++)
		{
			for (int k = 0;k < 3;k++)
			{
				tangdosang.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha*(A.at<Vec3b>(i, j)[k]) + beta);
			}
		}
	}
	return tangdosang;
}
void ImageLoad()
{
	if (myDetect.load("mycascade.xml"))
		cout << "done!" << endl;
	for (int i = 1; i <= 10; i++)
	{
		string dir1 = "D:/FPT/a";
		dir1.append(to_string(i));	
		dir1.append(".bmp");
		cout << dir1 << endl;
		Mat A;
		Mat kthuoc, gray, cut1, tangdosang1, cbsang;
		A = imread(dir1, 1);
		if (!A.empty())
		{
			tangdosang1 = TangDoSang(A);
			resize(tangdosang1, kthuoc, cv::Size(800, 600));	
			cbsang = CanBangAnhMau(kthuoc);

			cvtColor(cbsang, gray, CV_BGR2GRAY);
			blur(gray, gray, Size(3, 3));

			string dir2 = "D:/FPT/XAMXAM/xam";
			dir2.append(to_string(i));
			dir2.append(".png");
			imwrite(dir2, gray);
		}
	}
}
