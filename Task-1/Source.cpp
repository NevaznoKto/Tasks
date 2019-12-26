#include <iostream>
#include <string>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Scan.h"
using std::string;

string decode(std::vector<cv::Mat> &files)
{
	cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();

	for(auto iter = files.begin(); iter != files.end(); ++iter)
	{
		string code = qrDecoder.detectAndDecode(*iter);

		if (code[0] > '9')
			return code;
	}
	return "No found";
}

int main()
{
	using std::cout;
	using std::endl;

	std::vector<cv::Mat> files;
	char* Name_DIR = "../truth_search";
	scan_dir(Name_DIR, files);

	cout << files.size() << endl;

	cout << endl << endl << decode(files) << endl << endl;

	return 0;
}