#include <iostream>
#include <string>
#include <dirent.h>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::string;

string decode(string name)
{
	cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();

	cv::Mat inputImage = cv::imread(name);
	return qrDecoder.detectAndDecode(inputImage);
}

void scan_dir(const char* name_dir, string &code)
{
	DIR * dir_p;
	struct dirent * entry;

	dir_p = opendir(name_dir);

	wchar_t* txt = dir_p->wdirp->patt;
	std::wstring ws(txt);
	string direct(ws.begin(), ws.end() - 1);

	while ((entry = readdir(dir_p)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			string name(entry->d_name);
			code = decode(direct + name);

			if (code[0] > '9')
				break;
		}
	}
	closedir(dir_p);
}

int main()
{
	using std::cout;
	using std::endl;

	string data;
	char* Name_DIR = "../truth_search";
	scan_dir(Name_DIR, data);

	cout << endl << endl << data << endl << endl;

	return 0;
}