#include "MyForm.h"
#include "HaarCascade.h"
#include "ImageProcessing.h"
#include "SVM.h"
#include<iostream>
#include<fstream>
using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main()
{
	Mat image;
	HaarCascade myHaarCascade;

	myHaarCascade.LoadXML();
	string dir;
	for (int i = 0; i < 104; i++)
	{
		dir = "data/a";
		dir.append(to_string(i));
		dir.append(".bmp");
		cout << dir << endl;
		image = imread(dir, CV_LOAD_IMAGE_GRAYSCALE);
		if (!image.empty())
		{
			Mat licensePlate = myHaarCascade.DectectLicensePlate(image);
			if (licensePlate.cols == 150 && licensePlate.rows == 150)
			{
				vector<Rect> region = myHaarCascade.DetectRegion(licensePlate);
				vector<vector<Rect>> Position = myHaarCascade.OrderPostition(region);
				vector<vector<Mat>> number = myHaarCascade.DetectNumber(Position, licensePlate);
				SVMModel myClassify;
				for (int i = 0; i < number.size(); i++)
				{
					cout << "Hang " << i + 1 << ": ";
					myClassify.testing(number.at(i));
					for (int j = 0; j < number.at(i).size(); j++)
					{
						imshow("abc", number[i][j]);
						waitKey();
					}
					cout << endl;
				}
				imshow("image", myHaarCascade.DectectLicensePlate(image));
				//dir = "D:/FPT learn/TEST/a";
				//dir.append(to_string(i));
				//dir.append(".jpg");
				//imwrite(dir, myHaarCascade.DectectLicensePlate(image));
				waitKey(0);
			}
		}
	}
}