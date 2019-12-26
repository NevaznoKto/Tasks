#include <iostream>
#include <string>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Scan.h"
using std::vector;
using std::string;
using cv::Mat;

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