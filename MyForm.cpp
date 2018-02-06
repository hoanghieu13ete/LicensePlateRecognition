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
	Mat image, img;
	HaarCascade myHaarCascade;
	ifstream read;
	myHaarCascade.LoadXML();
	string dir, line;
	read.open("D:/FPT learn/Haar Training/testingdata/bg.txt");
	while (getline(read, line))
	{
		dir = "D:/FPT learn/Haar Training/testingdata/";
		dir.append(line);
		cout << dir << endl;
		image = imread(dir, CV_LOAD_IMAGE_GRAYSCALE);
		if (!image.empty())
		{
			vector<Rect> region;
			Mat licensePlate = myHaarCascade.DectectLicensePlate(image, region);
			if (licensePlate.cols == 150 && licensePlate.rows == 150)
			{ 
				vector<vector<Rect>> Position = myHaarCascade.OrderPostition(region);
				vector<vector<Mat>> number = myHaarCascade.DetectNumber(Position, licensePlate);

				SVMModel myClassify;
				for (int i = 0; i < number.size(); i++)
				{
					myClassify.testing(number.at(i));
				}

				//dir = "D:/FPT learn/TEST/a";
				//dir.append(to_string(i));
				//dir.append(".jpg");
				//imwrite(dir, myHaarCascade.DectectLicensePlate(image));
				imshow("licensePlate", licensePlate);
				waitKey(0);
			}
		}
	}
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//LicensePlateRecognition::MyForm form;
	//Application::Run(%form);
}