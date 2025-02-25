#pragma once
#include <string>


struct FolderData
{
private:
	int maxDays;
	std::string maxDaysTooltip;
	int maxSize;
	std::string maxSizeTooltip;
	int countFiles;
	std::string countFilesTooltip;
	std::string folderPath;	
public:
	FolderData();
	~FolderData();
};

