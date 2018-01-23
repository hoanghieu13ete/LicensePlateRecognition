#include "MyForm.h"
#include "HaarCascade.h"
#include "ImageProcessing.h"
#include <iostream>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main()
{
	Mat image = imread("D:/FPT learn/POSITIVE_IMAGE/a1.bmp", CV_LOAD_IMAGE_COLOR);
	cout << "1 " << endl;
	cvtColor(image, image, CV_BGR2GRAY);
	resize(image, image, Size(800, 600));
	HaarCascade myHaarCascade;
	myHaarCascade.LoadXML();
	imshow("detect", myHaarCascade.DectectLicensePlate(image));
	vector<Mat> number = myHaarCascade.DetectNumber(myHaarCascade.DectectLicensePlate(image));
	for (int i = 0; i < number.size(); i++)
	{
		imshow("num", number.at(i));
		waitKey(0);
	}
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//LicensePlateRecognition::MyForm form;
	//Application::Run(%form);
}