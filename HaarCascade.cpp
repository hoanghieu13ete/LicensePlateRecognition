#include"HaarCascade.h"


bool HaarCascade::LoadXML()
{
	return myDetect.load("mycascade.xml");
}

//return original image if it can't dectect License Plate.
Mat HaarCascade::DectectLicensePlate(Mat image)
{
	vector<Rect> rect;
	// dectect using haarcascade
	myDetect.detectMultiScale(image, rect);
	Mat cut;
	vector<vector<Point>> countours1;
	if (!rect.empty())
	{
		for (int i = 0; i < rect.size(); i++)
		{
			////cut by rectangle
			//cut = image(rect.at(i));
			//resize(cut, cut, Size(150, 150));

			//Mat binary;
			////binary to find countour
			//threshold(cut, binary, 200, 255, CV_THRESH_BINARY);

			////waitKey(0);
			//findContours(binary, countours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

			////if more than 9 object so it is a license plate.
			//for (size_t i = 0; i < countours1.size(); i++)
			//{
			//	int object = 0;
			//	Rect r = boundingRect(countours1[i]);

			//	if (r.width > 10 && r.height > 25)
			//	{
			//		object++;
			//	}
			//	
			//	cout << r.width << " " << r.height << endl;

			//	if (object > 5)
			//		return cut(r);
			//}
			rectangle(image, rect.at(i), Scalar(0, 255, 0), 1, 8, 0);
		}
		imshow("image", image);
		waitKey(0);
	}
	return image;
}

vector<Rect> HaarCascade::DetectRegion(Mat image)
{
	Mat binary;
	vector<Rect> region;

	GaussianBlur(image, binary, cv::Size(0, 0), 3);
	addWeighted(image, 1.5, binary, -0.5, 0, binary);

	adaptiveThreshold(binary, binary, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 5);

	imshow("binary", binary);
	waitKey(0);

	vector<vector<Point>> countours1;

	findContours(binary, countours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	//size of a number 20x50.
	for (size_t i = 0; i < countours1.size(); i++)
	{
		Rect r = boundingRect(countours1[i]);

		if (r.width > 10 && r.width < 30 && r.height > 40 && r.height < 60)
		{
			region.push_back(r);
		}
	}
	return region;
}

bool wayToSort(Rect x, Rect y)
{
	return x.x < y.x;
}

vector<Rect> SortRect(vector<Rect> x)
{
	sort(x.begin(), x.end(), wayToSort);
	return x;
}

// oder position 2 rows rect.
vector<vector<Rect>> HaarCascade::OrderPostition(vector<Rect> region)
{
	vector<vector<Rect>> number;
	vector<Rect> x1;
	vector<Rect> x2;
	for (int i = 0; i < region.size(); i++)
	{
		if (region.at(i).y < 50 && region.at(i).x > 20 && region.at(i).x < 130)
		{
			x1.push_back(region.at(i));
		}
		else if(region.at(i).y < 100 && region.at(i).x > 10 && region.at(i).x < 140)
		{
			x2.push_back(region.at(i));
		}
	}
	x1 = SortRect(x1);
	x2 = SortRect(x2);
	number.push_back(x1);
	number.push_back(x2);
	return number;
}

//dectect 2 rows number image.
vector<vector<Mat>> HaarCascade::DetectNumber(vector<vector<Rect>> number, Mat image)
{
	vector<vector<Mat>> numberDetect;
	vector<Mat> row1;
	vector<Mat> row2;
	Mat out;

	for (int j = 0; j < number[0].size(); j++)
	{
		Mat out = image(number[0][j]);
		resize(out, out, Size(12, 24));
		row1.push_back(out);
	}

	for (int j = 0; j < number[1].size(); j++)
	{
		Mat out = image(number[1][j]);
		resize(out, out, Size(12, 24));
		row2.push_back(out);
	}

	numberDetect.push_back(row1);
	numberDetect.push_back(row2);

	return numberDetect;
}