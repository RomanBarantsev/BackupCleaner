#pragma once
#include <vector>
#include <filesystem>
#include "FolderData.h"

#include <filesystem>
#include <unordered_set>
namespace fs = std::filesystem;

class Cleaner
{
private:
	bool protection=true;
	const std::vector<std::string> forbiddenFolders{
		"C:\\Users",
		"C:\\Windows",
		"C:\\Program Files",
		"C:\\Program Files (x86)",
		"C:\\ProgramData",
		"C:\\",
	};
	std::string folderPath;
	int daysToStore, countFiles;
	uintmax_t sizeOFolder;
private:
	std::vector<fs::directory_entry> files;
	std::vector<FolderData> Folders;
	void cleanByFolderSize();
	void cleanByCount();
	void cleanByAge();
	void getSortedFilesByTime();
public:
	Cleaner(std::string Folders,int days, int count, int size);
	~Cleaner();
	void clean();
};

