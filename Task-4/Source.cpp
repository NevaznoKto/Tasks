#include <iostream>
#include <string>
#include <dirent.h>

#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

using std::string;
using cv::Mat;
using std::cout;
using std::endl;

int PERSON_CLASS_ID = 15;

string toHMS(double mil)
{
	int MillisecondsInHour = 3600000;
	int MillisecondsInMinute = 60000;
	int MillisecondsInSecond = 1000;

	int H = static_cast<double>(mil) / MillisecondsInHour;
	mil -= H*MillisecondsInHour;
	int M = static_cast<double>(mil) / MillisecondsInMinute;
	mil -= M*MillisecondsInMinute;
	int S = static_cast<double>(mil) / MillisecondsInSecond;

	string out = std::to_string(H) + " Hours," + std::to_string(M) + " Minutes," + std::to_string(S) + " Seconds";
	return out;
}

int main()
{
	DIR * dir_p;
	struct dirent * entry;
	char* Name_DIR = "../endless_story";
	dir_p = opendir(Name_DIR);

	wchar_t* txt = dir_p->wdirp->patt;
	std::wstring ws(txt);
	string direct(ws.begin(), ws.end() - 1);

	string model = direct + "MobileNetSSD_deploy.caffemodel";
	string config = direct + "MobileNetSSD_deploy.prototxt";

	cv::dnn::Net net = cv::dnn::readNet(model, config);
	cv::VideoCapture cap = cv::VideoCapture(direct + "video.mp4");

	bool flag = true;
	double delta = 50 * cap.get(cv::CAP_PROP_FPS);
	double iter = 0;

	Mat frame, blob;
	while (flag)
	{
		cap.set(cv::CAP_PROP_POS_FRAMES, iter);
		cout << cap.get(cv::CAP_PROP_POS_FRAMES) << endl;

		cap >> frame;
		iter += delta;

		if (frame.empty())
		{
			break;
		}

		double scale = 1 / 127.5;
		int inpWidth = 300, inpHeight = 300;
		cv::Scalar mean(127.5, 127.5, 127.5);
		cv::dnn::blobFromImage(frame, blob, scale, cv::Size(inpWidth, inpHeight), mean);

		net.setInput(blob);
		Mat prob = net.forward();
		Mat prob_res = prob.reshape(1, 100);

		for (int j = 0; j < 100; ++j)
		{
			double confidence = prob_res.at<float>(j, 2);
			int classIdPoint = prob_res.at<float>(j, 1);

			if (confidence > 0.8 && classIdPoint == PERSON_CLASS_ID)
			{
				cout << "Class Object: " << classIdPoint << ",\n"
					<< "Confidence: " << confidence << ",\n"
					<< toHMS(cap.get(cv::CAP_PROP_POS_MSEC)) << endl;

				cv::imshow("WhatIsit", frame);
				flag = false;
				break;
			}
		}
	}

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}