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
	Mat image = imread("D:/FPT learn/POSITIVE_IMAGE/a2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	resize(image, image, Size(800, 600));

	HaarCascade myHaarCascade;
	myHaarCascade.LoadXML();
	vector<Mat> number = myHaarCascade.DetectNumber(myHaarCascade.DectectLicensePlate(image));

	//for (int i = 0; i < number.size(); i++)
	//{
	//	imshow("num", number.at(i));
	//	waitKey(0);
	//}

	SVMModel myClassify;
	myClassify.testing(number);
	imshow("detect", myHaarCascade.DectectLicensePlate(image));
	waitKey(0);
	_getch();

	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//LicensePlateRecognition::MyForm form;
	//Application::Run(%form);
}