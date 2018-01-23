#include"HaarCascade.h"

bool HaarCascade::LoadXML()
{
	return myDetect.load("mycascade.xml");
}
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
			//cut by rectangle
			cut = image(rect.at(i));

			Mat binary;
			//binary to find countour
			threshold(cut, binary, 200, 255, CV_THRESH_BINARY);
			waitKey(0);
			findContours(binary, countours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

			//if more than 9 object so it is a license plate.
			if (countours1.size() > 9)
			{
				Mat out;
				resize(cut, out, cv::Size(150, 150));
				return out;
			}
		}
	}
	return image;
}

vector<Mat> HaarCascade::DetectNumber(Mat image)
{
	vector<Mat> number;

	Mat binary;

	adaptiveThreshold(image, binary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 35, 5);

	vector<vector<Point>> countours1;

	findContours(binary, countours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	//size of a number 20x50.
	for (size_t i = 0; i < countours1.size(); i++)
	{
		Rect r = boundingRect(countours1[i]);

		if (r.width > 10 && r.width < 30 && r.height > 40 && r.height < 60)
		{
			number.push_back(image(r));
		}
	}

	return number;
}