#include <iostream>
#include <string>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching.hpp>

#include "Scan.h"
using std::vector;
using std::string;
using cv::Mat;

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