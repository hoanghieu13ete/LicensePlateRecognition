#include "MyForm.h"
#include "HaarCascade.h"
#include "ImageProcessing.h"
#include "SVM.h"
#include<iostream>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main()
{
	//Mat image;
	//HaarCascade myHaarCascade;

	//myHaarCascade.LoadXML();
	//string dir;
	//for (int i = 0; i < 104; i++)
	//{
	//	dir = "data/a";
	//	dir.append(to_string(i));
	//	dir.append(".bmp");
	//	cout << dir << endl;
	//	image = imread(dir, CV_LOAD_IMAGE_COLOR);

	//	if (!image.empty())
	//	{
	//		Mat licensePlate = myHaarCascade.DectectLicensePlate(image);
	//		if (licensePlate.cols == 150 && licensePlate.rows == 150)
	//		{
	//			vector<Rect> region = myHaarCascade.DetectRegion(licensePlate);
	//			vector<vector<Rect>> Position = myHaarCascade.OrderPostition(region);
	//			vector<vector<Mat>> number = myHaarCascade.DetectNumber(Position, licensePlate);
	//			SVMModel myClassify;
	//			for (int i = 0; i < number.size(); i++)
	//			{
	//				cout << "Hang " << i + 1 << ": ";
	//				myClassify.testing(number.at(i));
	//				for (int j = 0; j < number.at(i).size(); j++)
	//				{
	//					imshow("abc", number[i][j]);
	//					waitKey();
	//				}
	//				cout << endl;
	//			}
	//			imshow("image", myHaarCascade.DectectLicensePlate(image));
	//			//dir = "D:/FPT learn/TEST/a";
	//			//dir.append(to_string(i));
	//			//dir.append(".jpg");
	//			//imwrite(dir, myHaarCascade.DectectLicensePlate(image));
	//			waitKey(0);
	//		}
	//	}
	//}
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//LicensePlateRecognition::MyForm form;
	//Application::Run(%form);


	Mat image, output;
	string dir, dir1;
	ProcessImg test;
	for (int i = 10; i < 104; i++)
	{
		dir = "bs1/a";
		dir.append(to_string(i));
		dir.append(".jpg");
		cout << dir << endl;
		image = imread(dir, CV_LOAD_IMAGE_GRAYSCALE);
		if (!image.empty())
		{
			resize(image, image, Size(200, 200));
			
			adaptiveThreshold(image, image, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 35, 10);
			output = test.FindObject(image);
			//cout << dem<<endl;
			imshow("input", image);
			//imshow("dsa", output);

			//dir1 = "bs1/a";
			//dir1.append(to_string(i));
			//dir1.append(".jpg");
			//imwrite(dir1, image);
			waitKey();
			//_getch();
		}
	}
}