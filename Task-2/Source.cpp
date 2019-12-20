#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
	using std::vector;
	using std::string;
	using cv::Mat;
	vector<Mat> images;

	DIR * dir_p;
	struct dirent * entry;

	dir_p = opendir("../detective");

	wchar_t* txt = dir_p->wdirp->patt;
	std::wstring ws(txt);
	string direct(ws.begin(), ws.end() - 1);

	while ((entry = readdir(dir_p)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			string name(entry->d_name);
			Mat image = cv::imread(direct + name);
			images.push_back(image);
		}
	}

	closedir(dir_p);
	
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

				cv::imshow(name, dst_out);
		}
	}

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}