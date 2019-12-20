#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using std::vector;
using std::string;
using cv::Mat;

void scan_dir(const char* name_dir, vector<Mat> &files)
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
			Mat image = cv::imread(direct + name);
			files.push_back(image);
		}
	}
	closedir(dir_p);
}

int main()
{
	vector<Mat> images;
	char* Name_DIR = "../detective";
	scan_dir(Name_DIR, images);
	
	Mat dst_out; int k = 0;
	for (int i = 0; i < images.size(); ++i)
	{
		for (int j = i + 1; j < images.size(); ++j)
		{
				++k;
				dst_out = images[i] ^ images[j];

				string name("dst_");
				string s = std::to_string(i);
				name += s;
				s = std::to_string(j);
				name += s;

				//cv::imshow(name, dst_out);
				name += ".jpg";
				cv::imwrite(name, dst_out);
		}
	}

	images.clear();
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}