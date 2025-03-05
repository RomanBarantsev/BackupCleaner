#pragma once
#include <string>


struct FolderData
{
public:
	int maxDaysToStore;
	std::string maxDaysToStoreTooltip;
	int maxFolderSize;
	std::string maxFolderSizeTooltip;
	int countFiles;
	std::string countFilesTooltip;	
};

