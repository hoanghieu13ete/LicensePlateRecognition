//#pragma once
//#include<opencv2/imgcodecs/imgcodecs.hpp>
//#include<opencv2/highgui/highgui.hpp>
//
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <stdlib.h>
//#include<conio.h>
//#include <opencv2\core.hpp>
//#include <opencv2\highgui.hpp>
//#include <opencv2\opencv.hpp>
//#include <opencv2\imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//
//Mat Histogram(Mat input)
//{
//	Mat hsv, his;
//	cvtColor(input, hsv, CV_BGR2HSV);
//	vector<Mat>hsv_channels;
//	split(hsv, hsv_channels);	// tach lam 3 kenh mau
//	equalizeHist(hsv_channels[2], hsv_channels[2]);	// can bang his kenh mau (2): value
//	merge(hsv_channels, hsv);	// tron mau 
//	cvtColor(hsv, his, CV_HSV2BGR);
//	return his;
//}
//Mat Brightness(Mat input)
//{
//	Mat tangdosang;
//	tangdosang = input.clone();
//	double alpha = 1;
//	int beta = 2.5;
//	for (int i = 0;i < input.rows;i++)
//	{
//		for (int j = 0;j < input.cols;j++)
//		{
//			for (int k = 0;k < 3;k++)
//			{
//				tangdosang.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha*(input.at<Vec3b>(i, j)[k]) + beta);
//			}
//		}
//	}
//	return tangdosang;
//}
