#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching.hpp>

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
	char* Name_DIR = "../treasure_map";
	scan_dir(Name_DIR, images);


	cv::Stitcher::Mode mode = cv::Stitcher::SCANS;

	Mat pano;
	cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
	cv::Stitcher::Status status = stitcher->stitch(images, pano);
	if (status != cv::Stitcher::OK)
	{
		std::cout << "Can't stitch images, error code = " << int(status) << std::endl;
		return EXIT_FAILURE;
	}
	images.clear();

	string result_name = "result.jpg";
	imwrite(result_name, pano);
	std::cout << "stitching completed successfully, " << result_name << " saved!" << std::endl;

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}