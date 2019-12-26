#pragma once

#include <dirent.h>
#include <opencv2/highgui/highgui.hpp>

void scan_dir(const char* name_dir, std::vector<cv::Mat> &files);

std::string FullPathDirectory(const DIR * dir_p);