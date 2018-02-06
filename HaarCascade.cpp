#include"HaarCascade.h"


bool HaarCascade::LoadXML()
{
	return myDetect.load("mycascade.xml");
}

//return original image if it can't dectect License Plate.
Mat HaarCascade::DectectLicensePlate(Mat image, vector<Rect> &region)
{
	vector<Rect> rect;
	// dectect using haarcascade
	myDetect.detectMultiScale(image, rect, 1.05);
	Mat cut;
	vector<vector<Point>> countours1;
	if (!rect.empty())
	{
		for (int i = 0; i < rect.size(); i++)
		{
			Mat binary;
			//cut by rectangle
			cut = image(rect.at(i));
			resize(cut, cut, Size(150, 150));
			GaussianBlur(cut, binary, cv::Size(0, 0), 3);
			addWeighted(cut, 1.5, binary, -0.5, 0, binary);
			//binary to find countour
			adaptiveThreshold(cut, binary, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 5);
			dilate(binary, binary, Mat(Size(2, 2), CV_8U));
			//waitKey(0);
			findContours(binary, countours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
			int object = 0;
			//if more than 9 object so it is a license plate.
			for (size_t i = 0; i < countours1.size(); i++)
			{
				Rect r = boundingRect(countours1[i]);

				if (r.width > 10 && r.width < 30 && r.height > 30 && r.height < 60)
				{
					rectangle(binary, r, Scalar(0, 255, 0));
					region.push_back(r);
					object++;
				}
			}
			if (object > 8)
			{
				cout << object << endl;
				imshow("binary", binary);
				waitKey(0);
				return cut;
			}
		}
	}
	return image;
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
		if (region.at(i).y < 75 && region.at(i).x > 20 && region.at(i).x < 130)
		{
			x1.push_back(region.at(i));
		}
		else
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