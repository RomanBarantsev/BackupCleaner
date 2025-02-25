#pragma once
#include <vector>
#include <filesystem>
#include "FolderData.h"

class Cleaner
{
    
private:
	std::vector<FolderData> Folders;
	long long int getFolderSize(const std::string& folderPath);
	long long int getFileSize(const std::string& filePath);
	std::vector<std::string> getFiles(const std::string& folderPath);

public:
	Cleaner(std::vector<FolderData> Folders);
	~Cleaner();
	void clean();
};

