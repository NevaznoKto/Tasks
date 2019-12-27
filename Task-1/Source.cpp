#include <iostream>
#include <string>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Scan.h"
using std::string;

string decode(DIR * dir_p)
{
	cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();

	cv::Mat image;
	int err = 0;
	while(err != -1)
	{
		err = getOneFileInDir(dir_p, image);
		if (err == 0) 
		{
			string code = qrDecoder.detectAndDecode(image);

			if (code[0] > '9')
				return code;
		}
	}
	return "No found";
}

int main()
{
	using std::cout;
	using std::endl;

	char* Name_DIR = "../truth_search";
	DIR * dir_p;
	dir_p = opendir(Name_DIR);

	cout << endl << endl << decode(dir_p) << endl << endl;

	closedir(dir_p);
	return 0;
}