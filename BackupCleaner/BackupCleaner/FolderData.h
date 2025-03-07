#pragma once
#include <string>


struct FolderData
{
public:
	int daysToStore;
	std::string daysToStoreTooltip;
	int folderSize;
	std::string folderSizeTooltip;
	int countFiles;
	std::string countFilesTooltip;
	FolderData(int Days, std::string DaysTooltip, int Size, std::string SizeTooltip, int count, std::string countTooltip) :
		daysToStore(Days), daysToStoreTooltip(DaysTooltip), folderSize(Size),
		folderSizeTooltip(SizeTooltip), countFiles(count), countFilesTooltip(countTooltip) {
	}
};

