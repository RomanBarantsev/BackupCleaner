#include "Cleaner.h"

void Cleaner::cleanByFolderSize()
{
	uintmax_t totalSize = 0;
	//get all files by date then iterate, and counting and if it more then delete last ones. 
	sizeOFolder = sizeOFolder * 1024 * 1024;
	for (const auto& entry : files) {
		if (fs::is_regular_file(entry)) {
			totalSize += fs::file_size(entry);
			if (totalSize > sizeOFolder)
			{
				totalSize -= fs::file_size(entry);
				fs::remove(entry);
			}
		}
	}
}

void Cleaner::cleanBySize(std::vector<fs::directory_entry>& files)
{

}

void Cleaner::cleanByAge()
{

}

void Cleaner::getSortedFilesByTime()
{
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (fs::is_regular_file(entry)) {
			files.push_back(entry);
		}
	}
	std::sort(files.rbegin(), files.rend(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
		return fs::last_write_time(a) < fs::last_write_time(b);
		});
}


Cleaner::Cleaner(std::string path, int days, int count, int size) : folderPath(path), daysToStore(days), countFiles(count), sizeOFolder(size)
{
	if (folderPath == "")
		return;
	getSortedFilesByTime();
	clean();
}

Cleaner::~Cleaner()
{

}

void Cleaner::clean()
{	
	if (daysToStore!=0) {

	}
	if (countFiles != 0) {

	}
	if (sizeOFolder != 0) {
		cleanByFolderSize();
		
	}
}
