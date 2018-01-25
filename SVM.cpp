//

#include "SVM.h"

void setDataTraining(vector<Mat> &trainCells) {
	string dir = "dataTraining1/";
	string path;
	Mat img;
	for (int i = 0; i <= 26; i++) {
		for (int j = 1; j <= 20; j++) {
			path = dir + to_string(i) + "_" + to_string(j) + ".jpg";
			img = imread(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
			if (!img.empty()) {
				trainCells.push_back(img);
			}
			else {
				path = dir + to_string(i) + "_" + to_string(j) + ".png";
				img = imread(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
				if (!img.empty()) {
					trainCells.push_back(img);
				}
				else cout << "flie " << path << " not exist" << endl;
			}
			//cout << "flie " << path << " not exist" << endl;

		}
	}
}
void setLabelTraining(vector<int> &trainLabel) {
	for (int i = 0; i <= 26; i++) {
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
void setHOG(vector<vector<float> > &trainHOG, vector<Mat> &trainCells) {
	for (int i = 0; i < trainCells.size(); i++) {
		vector<float> descriptors;
		hog.compute(trainCells[i], descriptors);
		trainHOG.push_back(descriptors);
	}
}

void setMatrix(vector<vector<float> > &trainHOG, Mat &trainMat) {
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
void setDataTesing(vector<Mat> &testCells) {
	string dir = "img_testing/test_";
	string path;
	Mat img;
	for (int i = 1; i <= 14; i++) {
		path = dir + to_string(i) + ".jpg";
		img = imread(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		if (!img.empty()) {
			testCells.push_back(img);
		}
		else {
			path = dir + to_string(i) + ".png";
			img = imread(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
			if (!img.empty()) {
				testCells.push_back(img);
			}
			else cout << "flie " << path << " not exist" << endl;
		}
	}
}

void printResult(Mat &testResponse) {
	vector <string> result;
	for (int i = 0; i < testResponse.rows; i++) {
		if (testResponse.at<float>(i, 0) == 10) {
			cout << "B ";
			result.push_back("B");
		}
		else if (testResponse.at<float>(i, 0) == 11) {
			cout << "C ";
			result.push_back("C");
		}
		else if (testResponse.at<float>(i, 0) == 12) {
			cout << "E ";
			result.push_back("E");
		}
		else if (testResponse.at<float>(i, 0) == 13) {
			cout << "F ";
			result.push_back("F");
		}
		else if (testResponse.at<float>(i, 0) == 14) {
			cout << "G ";
			result.push_back("G");
		}
		else if (testResponse.at<float>(i, 0) == 15) {
			cout << "H ";
			result.push_back("H");
		}
		else if (testResponse.at<float>(i, 0) == 16) {
			cout << "K ";
			result.push_back("K");
		}
		else if (testResponse.at<float>(i, 0) == 17) {
			cout << "L ";
			result.push_back("L");
		}
		else if (testResponse.at<float>(i, 0) == 18) {
			cout << "Z ";
			result.push_back("Z");
		}
		else if (testResponse.at<float>(i, 0) == 19) {
			cout << "M ";
			result.push_back("M");
		}
		else if (testResponse.at<float>(i, 0) == 20) {
			cout << "P ";
			result.push_back("P");
		}
		else if (testResponse.at<float>(i, 0) == 21) {
			cout << "R ";
			result.push_back("R");
		}
		else if (testResponse.at<float>(i, 0) == 22) {
			cout << "S ";
			result.push_back("S");
		}
		else if (testResponse.at<float>(i, 0) == 23) {
			cout << "T ";
			result.push_back("T");
		}
		else if (testResponse.at<float>(i, 0) == 24) {
			cout << "U ";
			result.push_back("U");
		}
		else if (testResponse.at<float>(i, 0) == 25) {
			cout << "V ";
			result.push_back("V");
		}
		else if (testResponse.at<float>(i, 0) == 26) {
			cout << "X ";
			result.push_back("X");
		}
		else { 
			cout << testResponse.at<float>(i, 0) << " ";
			result.push_back(to_string(testResponse.at<float>(i, 0)));
		}
	}
}

void SVMModel::training()
{
	vector<Mat> trainCells;
	setDataTraining(trainCells);
	///////
	vector<int> trainLabels;
	setLabelTraining(trainLabels);

	vector<vector<float> > trainHOG;
	setHOG(trainHOG, trainCells);


	int descriptor_size = trainHOG[0].size();

	cout << descriptor_size;
	Mat trainMat(trainHOG.size(), descriptor_size, CV_32FC1);

	setMatrix(trainHOG, trainMat);

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


Mat SVMModel::testing(vector<Mat> &testCells)
{

	vector<vector<float> > testHOG;

	setHOG(testHOG, testCells);
	//////////
	int descriptor_size = testHOG[0].size();
	Mat testMat(testHOG.size(), descriptor_size, CV_32FC1);
	/////////
	setMatrix(testHOG, testMat);

	Ptr<SVM> trainedModel = StatModel::load<SVM>("digitsClassitify.yml");
	Mat result;

	svmPredict(trainedModel, result, testMat);

	printResult(result);
	return result;
}


