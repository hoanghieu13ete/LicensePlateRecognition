#include "MyForm.h"
#include "HaarCascade.h"
#include "ImageProcessing.h"
#include<iostream>
using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LicensePlateRecognition::MyForm form;
	Application::Run(%form);
}