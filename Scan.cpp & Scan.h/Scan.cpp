#include "Scan.h"

void scan_dir(const char* name_dir, std::vector<cv::Mat> &files)
{
	files.clear();

	DIR * dir_p;
	dir_p = opendir(name_dir);

	struct dirent * entry;
	std::string direct = FullPathDirectory(dir_p);

	while ((entry = readdir(dir_p)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			std::string name(entry->d_name);
			cv::Mat image = cv::imread(direct + name);
			files.push_back(image);
		}
	}

	closedir(dir_p);
}

std::string FullPathDirectory(const DIR * dir_p)
{
	wchar_t* txt = dir_p->wdirp->patt;
	std::wstring ws(txt);
	std::string direct(ws.begin(), ws.end() - 1);

	return direct;
}
