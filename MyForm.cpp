#include "MyForm.h"
#include <opencv2/highgui/highgui.hpp>
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LicensePlateRecognition::MyForm form;
	Application::Run(%form);
}