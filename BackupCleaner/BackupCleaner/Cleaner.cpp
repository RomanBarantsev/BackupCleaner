#include "Cleaner.h"
#include <filesystem>
namespace fs = std::filesystem;

long long int Cleaner::getFolderSize(const std::string& folderPath)
{

	return 0;
}

long long int Cleaner::getFileSize(const std::string& filePath)
{
	return 0;
}

std::vector<std::string> Cleaner::getFiles(const std::string& folderPath)
{
	std::vector<std::string> files;
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (fs::is_regular_file(entry.path()))
		{
			files.push_back(entry.path().string());
		}
	}
	return std::vector<std::string>();
}

Cleaner::Cleaner(std::vector<FolderData> Folders)
{
}

Cleaner::~Cleaner()
{

}

void Cleaner::clean()
{
	for (auto& folder : Folders)
	{

	}
}
