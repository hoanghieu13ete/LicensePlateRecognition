#include "MyForm.h"
#include "HaarCascade.h"
#include "ImageProcessing.h"
#include "SVM.h"
#include<iostream>
#include <conio.h>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main()
{
	Mat image = imread("D:/Program Files (x86)/svm/traning_svm/data/xam1.png", CV_LOAD_IMAGE_GRAYSCALE);
	HaarCascade myHaarCascade;
	myHaarCascade.LoadXML();
	//imshow("detect", myHaarCascade.DectectLicensePlate(image));
	vector<Mat> number = myHaarCascade.DetectNumber(myHaarCascade.DectectLicensePlate(image));
	/*for (int i = 0; i < number.size(); i++)
	{
		imshow("num", number.at(i));
		waitKey(0);
	}*/
	Mat result;
	SVMModel prediction;
	result = prediction.testing(number);
	_getch();
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//LicensePlateRecognition::MyForm form;
	//Application::Run(%form);
}