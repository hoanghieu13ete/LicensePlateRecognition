#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include "ImageProcessing.h"



using namespace std;
using namespace cv;
//	can bang mau
Mat Histogram(Mat &input)
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
// tang giam do sang
Mat Brightness(Mat &input)
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
// ham xu li anh dau vao
Mat ProcessImg::ProImg(Mat &input)	// cho anh duoc can bang do sang + mau
{
	Mat kthuoc, xam, cat, tangdosang1, cbsang, output;
	int mau;
	if (!input.empty())
	{
		tangdosang1 = Brightness(input);
		//resize(tangdosang1, kthuoc, cv::Size(800, 600));
		cbsang = Histogram(tangdosang1);
		output = cbsang;
	}
	return output;
}

// chuyen doi mau cua anh, sang thanh toi va nguoc lai
Mat InvertImg(Mat &input)
{
	Mat output = input;
	//
	for (int i = 0;i < input.rows;i++)
	{
		for (int j = 0;j < input.cols;j++)
		{
			output.at<uchar>(i, j) = 255 - (int)input.at<uchar>(i, j);
		}
	}
	return output;
}
//	xac dinh mau, anh vao la anh ra co nen trang chu den
Mat ProcessImg::Color(Mat &input)
{
	Mat hsv, xanh, ddo1, ddo2, output;
	cvtColor(input, hsv, CV_BGR2HSV);
	// detect mau xanh
	inRange(hsv, Scalar(20, 10, 80), Scalar(170, 250, 200), xanh);
	// detect mau do
	inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), ddo1);
	inRange(hsv, Scalar(110, 50, 50), Scalar(180, 255, 255), ddo2);
	Mat1b ddo = ddo1 | ddo2;

	float mdo, mxanh;
	// dem diem trang cua anh mau do, mau xanh
	mdo = countNonZero(ddo);
	cout << mdo << endl;
	mxanh = countNonZero(xanh);
	cout << mxanh << endl;

	// dem tong so pixel cua anh 
	float pixel = hsv.rows*hsv.cols;
	cout << pixel << endl;

	cout << endl << "0.TRANG 1.DO 2.XANH\t\t";
	int mau;
	if (mdo > mxanh && mdo / pixel > 0.4)
	{
		mau = 1;
		cout << mau << endl;
	}
	else if (mxanh > mdo && mxanh / pixel > 0.4)
	{
		mau = 2;
		cout << mau << endl;
	}
	else
	{
		mau = 0;
		cout << mau << endl;
	}
	if (mau == 1)
	{
		output = InvertImg(ddo);
	}
	else if (mau == 2)
	{
		output = InvertImg(xanh);
	}
	else
	{
		for (int i = 0;i < input.rows;i++)
		{
			for (int j = 0;j < input.cols;j++)
			{
				for (int k = 0;k < 3;k++)
				{
					if ((int)input.at<Vec3b>(i, j)[k] < 130)
					{
						input.at<Vec3b>(i, j)[k] = 30;
					}
					else
						input.at<Vec3b>(i, j)[k] = 255;
				}
			}
		}
		output = input.clone();
	}
	return output;
}//

Mat ProcessImg::Dilate(Mat &input)
{
	Mat output, element;
	element = getStructuringElement(MORPH_RECT, Size(2,2), Point(1,1));
	adaptiveThreshold(input, input, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 35, 10);
	GaussianBlur(input, input, Size(9, 9), 0, 0);
	erode(input, output, element);
	//imshow("asdgkgjsg", output);
	return output;
}
//Mat ProcessImg::CutImg(Mat &input, int vtri1, int vtri2, int dai, int rong)
//{	
//	Mat cut;
//	Rect rect(vtri1, vtri2, dai, rong);
//	//rectangle(input, rect, Scalar(0, 255, 0));
//	cut = input(rect);
//	return cut;
//}
//Mat ProcessImg::FindObject(Mat &input)
//{
//	vector<vector<Point>> countours1;
//	vector<Vec4i> hierarchy;
//	vector<int> selected;
//	int a, b, c, d;
//	findContours(input, countours1, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//	Mat drawing = Mat::zeros(input.size(), CV_8UC3);
//	for (int i = 0; i < countours1.size(); i++)
//	{
//		Scalar color = Scalar(0, 255, 0);
//		Rect R = boundingRect(countours1[i]);
//		// filter contours according to their bounding box
//		if (R.width > 10 && R.width <50 && R.height > 30 && R.height <80)
//		{
//			selected.push_back(i);
//			drawContours(drawing, countours1, i, color, 2, 8, hierarchy, 0, Point());
//			a = R.x;b = R.y; c = R.width;d = R.height;
//			cout << a << "\t" << b << "\t" << c << "\t" << d << endl;
//		}
//		for (size_t i = 0; i < selected.size(); i++)
//		{
//			Rect rect(a, b, 20, 60);
//			rectangle(input, rect, Scalar(0, 255, 0), 1);
//			//rectangle(input, boundingRect(countours1[selected[i]]), Scalar(0, 255, 0), 1);
//		}
//	}
//	//for (size_t i = 0; i < selected.size(); i++)
//	//{
//	//	Rect R = boundingRect(countours1[i]);
//	//	Rect rect(R.x, R.y, 30, 30);
//	//	rectangle(input, boundingRect(countours1[selected[i]]), Scalar(0, 255, 0), 1);
//	//	
//	//}
//
//
//	//for (int i = 0;i <= countours1.size();i++)
//	//{
//	//	Rect r = boundingRect(countours1[i]);
//	////	if (r.width > 10 && r.width < 30 && r.height > 40 && r.height < 60)
//	////	{
//	////		cout << r.width << " " << r.height << endl;
//	////		object++;			
//	////	}		
//	//}
//	cout<<"sdfaff\t";
//	cout << selected.size() <<endl;
//	return input;
//}