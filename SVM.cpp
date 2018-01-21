#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/ml.hpp>
#include <conio.h>

using namespace cv::ml;
using namespace cv;
using namespace std;

void setDataTraining(vector<Mat> &trainCells) {
	string dir = "trainingData/";
	string path;
	Mat img;
	for (int i = 0; i <= 9; i++) {
		for (int j = 1; j <= 20; j++) {
			path = dir + to_string(i) + "_" + to_string(j) + ".jpg";
			img = imread(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
			if (img.empty()) {
				cout << "flie " << path << " not exist" << endl;
			}
			else trainCells.push_back(img);
		
		}
	}
}
void setLabelTraining(vector<int> &trainLabel) {
	for (int i = 0; i <= 9; i++) {
		for (int j = 1; j <= 20; j++) {
			trainLabel.push_back(i);
		}
	}
}
HOGDescriptor hog(
	Size(12, 24), //winSize
	Size(4, 8), //blocksize
	Size(2, 4), //blockStride,
	Size(4, 8), //cellSize,
	9, //nbins,
	1, //derivAper,
	-1, //winSigma,
	0, //histogramNormType,
	0.2, //L2HysThresh,
	0,//gammal correction,
	64,//nlevels=64
	1);
void setTrainHOG(vector<vector<float> > &trainHOG, vector<Mat> &trainCells) {
	for (int i = 0; i < trainCells.size(); i++) {
		vector<float> descriptors;
		hog.compute(trainCells[i], descriptors);
		trainHOG.push_back(descriptors);
	}
}

void setMatrixTraining(vector<vector<float> > &trainHOG, Mat &trainMat) {
	int descriptor_size = trainHOG[0].size();
	for (int i = 0; i<trainHOG.size(); i++) {
		for (int j = 0; j<descriptor_size; j++) {
			trainMat.at<float>(i, j) = trainHOG[i][j];
		}
	}
}

Ptr<SVM> svmInit(float C, float gamma)
{
	Ptr<SVM> svm = SVM::create();
	svm->setGamma(gamma);
	svm->setC(C);
	svm->setKernel(SVM::RBF);
	svm->setType(SVM::C_SVC);

	return svm;
}

void svmTrain(Ptr<SVM> svm, Mat &trainMat, vector<int> &trainLabels)
{
	Ptr<TrainData> td = TrainData::create(trainMat, ROW_SAMPLE, trainLabels);
	svm->train(td);
	svm->save("digitsClassitify.yml");
	cout << "Training complete !" << endl;
}

void svmPredict(Ptr<SVM> svm, Mat &testResponse, Mat &testMat)
{
	svm->predict(testMat, testResponse);
}

void SVMevaluate(Mat &testResponse, float &count, float &accuracy, vector<int> &testLabels)
{
	for (int i = 0; i < testResponse.rows; i++)
	{
		if (testResponse.at<float>(i, 0) == testLabels[i])
			count = count + 1;
	}
	accuracy = (count / testResponse.rows) * 100;
}


void training() {
	vector<Mat> trainCells;
	setDataTraining(trainCells);
	///////
	vector<int> trainLabels;
	setLabelTraining(trainLabels);
	////////
	vector<vector<float> > trainHOG;
	setTrainHOG(trainHOG, trainCells);

	int descriptor_size = trainHOG[0].size();


	Mat trainMat(trainHOG.size(), descriptor_size, CV_32FC1);
	////////////
	setMatrixTraining(trainHOG, trainMat);

	//training
	float C = 12.5, gamma = 0.5;

	Ptr<SVM> model = svmInit(C, gamma);

	svmTrain(model, trainMat, trainLabels);
	//Testing
	Mat testResponse;
	svmPredict(model, testResponse, trainMat);
	// accuracy
	float count = 0;
	float accuracy = 0;	
	SVMevaluate(testResponse, count, accuracy, trainLabels);
	cout << "the accuracy is :" << accuracy << endl;
}

void setDataTesing(vector<Mat> &testCells) {
	string dir = "imgTesting/test_";
	string path;
	Mat img;
	for (int i = 1; i <= 9; i++) {
		path = dir + to_string(i) + ".jpg";
		img = imread(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		if (img.empty()) {
			cout << "flie " << path << " not exist" << endl;
		}
		else testCells.push_back(img);
	}
}

void printResult(Mat &testResponse) {
	for (int i = 0; i < testResponse.rows; i++) {
		cout << testResponse.at<float>(i, 0) << " ";
	}
}

void testing() {
	vector<Mat> testCells;
	vector<vector<float> > testHOG;
	setDataTesing(testCells);
	setTrainHOG(testHOG, testCells);
	//////////
	int descriptor_size = testHOG[0].size();
	Mat testMat(testHOG.size(), descriptor_size, CV_32FC1);
	/////////
	setMatrixTraining(testHOG, testMat);

	Ptr<SVM> trainedModel = StatModel::load<SVM>("digitsClassitify.yml");
	Mat result;
	svmPredict(trainedModel, result, testMat);

	printResult(result);

}
