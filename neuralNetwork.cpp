#include "neuralNetwork.h"
#include "SVM.h"
#include < conio.h>
#include <stdint.h>
#include <fstream>

//trainingCells --> HOGMat --> traingMat
//vector labels --> onehot ---> trainingMat

void setDataTraining1(vector<Mat> &trainCells, vector<int> label) {
	Mat img;
	string text;
	ifstream file;
	file.open("D:/Program Files (x86)/svm/data1/DataOrder/bg.txt");

	//for (int i = 0; i <= 9; i++) {
	//	for (int j = 1; j <= 20; j++) {
	//		path = dir + to_string(i) + "_" + to_string(j) + ".jpg";
	//		img = imread(path.c_str(), 1);
	//		
	//		if (!img.empty()) {
	//			cvtColor(img, img, CV_BGR2GRAY);
	//			threshold(img, img, 100, 255, THRESH_BINARY);
	//			trainCells.push_back(img);
	//		}
	//		else {
	//			path = dir + to_string(i) + "_" + to_string(j) + ".png";
	//			img = imread(path.c_str(), 1);
	//			if (!img.empty()) {
	//				cvtColor(img, img, CV_BGR2GRAY);
	//				threshold(img,img, 100, 255, THRESH_BINARY);
	//				trainCells.push_back(img);
	//			}
	//			else cout << "flie " << path << " not exist" << endl;
	//		}
	//		//cout << "flie " << path << " not exist" << endl;

	//	}
	while (getline(file, text))
	{
		img = imread(text, CV_LOAD_IMAGE_GRAYSCALE);
		trainCells.push_back(img);
		text = text.substr(0, text.find('_'));
		label.push_back(stoi(text));
	}
	file.close();
}
// trainingCells

//HOGDescriptor hog1(Size(12, 24),Size(4, 8),Size(2, 4), Size(4, 8), 9,1, -1, 0, 0.2, 0, 64, 1);

void setFeature(vector<Mat> &feature, vector<Mat> &trainCells) {
	Mat temp;
	for (int i = 0; i < trainCells.size(); i++) {
		temp = trainCells[i].reshape(1, 1);
		feature.push_back(temp);
	}
}

Mat setMatrix1(vector<Mat> &feature) {
	int descriptor_size = feature[0].cols;
	Mat trainMat(feature.size(), descriptor_size, CV_32FC1);
	for (int i = 0; i < feature.size(); i++) {
		for (int j = 0; j < descriptor_size; j++) {
			trainMat.at<float>(i, j) = (float)feature[i].at<uint8_t>(0, j);
			//cout << (float)feature[i].at<uint8_t>(0,j) << ",";
		}
		//cout << "*" << endl;
	}
	return trainMat;
}

void setLabelVector(vector<int> &vectorLabels) {
	for (int i = 0; i <= 9; i++) {
		for (int j = 1; j <= 20; j++) {
			vectorLabels.push_back(i);
		}
	}
}

Mat oneHot(vector<int> &vectorLabels) {
	Mat matLabels = Mat::zeros((int)vectorLabels.size(), 10, CV_32FC1);
	for (int i = 0; i < matLabels.rows; i++) {
		matLabels.at<int>(i, vectorLabels[i]) = 1;
	}
	return matLabels;
}

void printLabelsAfterOneHot(Mat &matLabels) {
	for (int i = 0; i < matLabels.rows; i++) {
		for (int j = 0; j < matLabels.cols; j++) {
			cout << matLabels.at<int>(i, j) << " ";
		}
		cout << endl;
	}
}

Ptr<ANN_MLP> intAnn() {
	Mat layerSize = Mat(1, 5, CV_32SC1);
	layerSize.at<int>(0) = 288;
	layerSize.at<int>(1) = 400;
	layerSize.at<int>(2) = 400;
	layerSize.at<int>(3) = 400;
	layerSize.at<int>(4) = 10;
	Ptr<ANN_MLP> ann = ANN_MLP::create();
	ann->setLayerSizes(layerSize);
	ann->setActivationFunction(ANN_MLP::SIGMOID_SYM);
	ann->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 20, FLT_EPSILON));
	ann->setTrainMethod(ANN_MLP::BACKPROP, 0.001);
	return ann;
}

void annTrain(Ptr<ANN_MLP> ann, Mat &trainMat, Mat &matLabels) {
	Ptr<TrainData> td = TrainData::create(trainMat, ROW_SAMPLE, matLabels);
	ann->train(td);
	ann->save("digitsClassitify_ann.yml");
	cout << "Training complete !";
}
void prediction(Ptr<ANN_MLP> ann, Mat &testMax) {
	Mat tempMax(1, 288, CV_32FC1);
	for (int i = 0; i < testMax.rows; i++) {
		tempMax = testMax.at<float>(i);
		int result = (int)ann->predict(tempMax);
		cout << result << endl;
	}
}
void neuralNetwork::training()
{
	//vector<Mat> trainCells;
	//setDataTraining1(trainCells);

	//vector<Mat> feature;
	//setFeature(feature, trainCells);

	//Mat trainMat = setMatrix1(feature);
	/////////////////////// complete x
	//vector<int> vectorLabels;

	//setLabelVector(vectorLabels);

	//Mat matLabels = oneHot(vectorLabels);

	//////printLabelsAfterOneHot(matLabels);
	//////////////////////////////// complete y

	//Ptr<ANN_MLP> ann = intAnn();
	//annTrain(ann, trainMat, matLabels);
	//Ptr<ANN_MLP> annTrained = StatModel::load<ANN_MLP>("digitsClassitify_ann.yml");
	//Mat result;
	////annTrained->predict(trainMat, result);
	////printLabelsAfterOneHot(result);
	//prediction(ann, trainMat);

}

vector<string> neuralNetwork::testing(vector<Mat>& testMat)
{
	return vector<string>();
}
