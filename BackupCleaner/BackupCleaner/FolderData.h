#pragma once
#include <string>


struct FolderData
{
private:
	int maxDaysToStore;
	std::string maxDaysToStoreTooltip;
	int maxFolderSize;
	std::string maxFolderSizeTooltip;
	int countFiles;
	std::string countFilesTooltip;
public:
	FolderData();
	~FolderData() {};
};

