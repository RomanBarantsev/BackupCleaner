#pragma once
#include <string>


struct FolderData
{
public:
	int* daysToStore;
	int* folderSize;
	int* countFiles;
	FolderData(int Days, int Size, int count) {
		daysToStore = new int(Days);
		folderSize = new int(Size);
		countFiles = new int(count);
	}
	~FolderData() {
		delete daysToStore;
		delete folderSize;
		delete countFiles;
		daysToStore = nullptr;
		folderSize = nullptr;
		countFiles = nullptr;
	}
};

