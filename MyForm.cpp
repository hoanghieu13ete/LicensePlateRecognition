#include "MyForm.h"
#include "HaarCascade.h"
#include "ImageProcessing.h"
#include "SVM.h"
#include<iostream>
#include<conio.h>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main()
{
	Mat image = imread("D:/FPT learn/POSITIVE_IMAGE/a6.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	resize(image, image, Size(800, 600));
	HaarCascade myHaarCascade;

	myHaarCascade.LoadXML();

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
			cout << endl;
		}
		imshow("image", myHaarCascade.DectectLicensePlate(image));
		waitKey(0);
		_getch();
	}
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//LicensePlateRecognition::MyForm form;
	//Application::Run(%form);
}