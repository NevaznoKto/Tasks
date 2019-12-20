#include <iostream>
#include <string>
#include <dirent.h>

#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

std::string decode(std::string name)
{
	cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();

	cv::Mat inputImage = cv::imread(name);
	return qrDecoder.detectAndDecode(inputImage);
}

int main()
{
	using std::string;
	using std::cout;
	using std::endl;

	int file_count = 0;

	DIR * dir_p;
	struct dirent * entry;

	string data;
	dir_p = opendir("../truth_search");

	wchar_t* txt = dir_p -> wdirp -> patt;
	std::wstring ws(txt);
	string direct(ws.begin(), ws.end() - 1);

	while ((entry = readdir(dir_p)) != NULL)
	{
		if (entry -> d_type == DT_REG) 
		{
			file_count++;
			cout << file_count << "  ";

			string name(entry -> d_name);
			data = decode(direct + name);

			if (data[0] > '9')
				break;
		}
	}

	closedir(dir_p);

	cout << endl << endl << data << endl << endl;

	return 0;
}