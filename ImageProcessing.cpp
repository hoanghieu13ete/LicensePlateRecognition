#include "ImageProcessing.h"


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
// tang giam do sang
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
// cat anh
Mat CutImg(Mat input)
{
	cout << "Nhap vtri1, vtri2, chieu dai va chieu rong. \n";
	int vtri1, vtri2, chieurong, chieudai; // dua vao vtri va kich thuoc can cat
										   /*cin >> vtri1 >> vtri2 >> chieurong >> chieudai;
										   cout << endl;*/
	Rect r = Rect(vtri1, vtri2, chieurong, chieudai);
	rectangle(input, r, CV_RGB(255, 0, 255), 5, 4); // ve hinh chu nhat vao anh 
	Mat a(input, r);	// cat phan hinh chu nhat da ve
	return a;
}
// Xoay anh
Mat Rotate(Mat input)
{
	double angle = 90;
	Point2f center(input.cols / 2., input.rows / 2.);
	Mat r = cv::getRotationMatrix2D(center, angle, 1.0);
	Mat dst;
	warpAffine(input, dst, r, input.size());
	return dst;
}
Mat ProcessImgTest::ProcessImg(Mat input)
{
	Mat kthuoc, output, cat, tangdosang1, cbsang;
	if (!input.empty())
	{
		tangdosang1 = Brightness(input);
		resize(tangdosang1, kthuoc, cv::Size(800, 600));
		cbsang = Histogram(kthuoc);

		cvtColor(cbsang, output, CV_BGR2GRAY);
		blur(output, output, Size(3, 3));
	}
	return output;
}
//	lam net anh
Mat Sharp(Mat input)
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
//	xac dinh mau
Mat ProcessImgTest::Color(Mat input)
{
	Mat hsv, xanh, ddo1, ddo2, output;
	cvtColor(input, hsv, CV_BGR2HSV);
	// detect mau xanh
	inRange(hsv, Scalar(50, 10, 80), Scalar(170, 250, 200), xanh);
	// detect mau do
	inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), ddo1);
	inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), ddo2);
	Mat1b ddo = ddo1 | ddo2;

	float mdo, mxanh;
	// dem diem trang cua anh mau do, mau xanh
	mdo = countNonZero(ddo);
	mxanh = countNonZero(xanh);

	// dem tong so pixel cua anh 
	float pixel = hsv.rows*hsv.cols;

	cout << endl << "0.TRANG 1.DO 2.XANH\t\t";
	int mau;
	if (mdo / pixel > 0.6)
	{
		mau = 1;
		cout << mau << endl;
	}
	else if (mxanh / pixel > 0.6)
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
		output = Sharp(ddo);
	}
	else if (mau == 2)
	{
		output = Sharp(xanh);
	}
	else output = hsv;
	return output;
}
Mat LocCanny_GianNo(Mat input)
{
	//cvtColor(A, CV_LOAD_IMAGE_GRAYSCALE);
	Mat Canny1, dilate1, erode1, output;
	//loc anh
	blur(input, input, Size(3, 3));
	GaussianBlur(input, input, cv::Size(0, 0), 3);
	Canny(input, Canny1, 60, 160, 3);
	output = Canny1.clone();
	//// gian no + co nen
	//dilate(Canny1, dilate1, 18);
	//erode(dilate1, erode1, 18);
	return output;
}