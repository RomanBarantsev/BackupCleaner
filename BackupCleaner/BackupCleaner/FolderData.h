#pragma once
#include <string>


struct FolderData
{
public:
	int daysToStore;
	int folderSize;
	int countFiles;
	FolderData(int Days, int Size, int count) :
		daysToStore(Days), folderSize(Size), countFiles(count) {
	}
};

