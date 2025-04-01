#include "Cleaner.h"
#include <chrono>

namespace fs = std::filesystem;

void Cleaner::cleanByFolderSize()
{
	uintmax_t totalSize = 0;
	//get all files by date then iterate, and counting and if it more then delete last ones. 
	sizeOFolder = sizeOFolder * 1024 * 1024;
	for (const auto& file : files) {
		if (fs::is_regular_file(file)) {
			totalSize += fs::file_size(file);
			if (totalSize > sizeOFolder)
			{
				totalSize -= fs::file_size(file);
				fs::remove(file);
			}
		}
	}
}

void Cleaner::cleanByCount()
{
	int counter{0};
	for (const auto& file : files) {		
		if (counter >= countFiles) {
			fs::remove(file);
		}
		else {
			counter++;
		}
	}
}


void Cleaner::cleanByAge()
{
	using namespace std::chrono;
	using Day = std::chrono::days;
	using std::chrono::duration_cast;
	auto start = std::chrono::system_clock::now();
	auto midnight = std::chrono::floor<Day>(start); 
	auto midnightToday = time_point_cast<system_clock::duration>(midnight);
	auto cutoffTime = midnightToday - std::chrono::hours(24 * (daysToStore-1));
	for (const auto& file : files) {
		if (fs::is_regular_file(file)) {
			auto ftime = fs::last_write_time(file);
			auto sysTime = clock_cast<std::chrono::system_clock>(ftime);
			if (sysTime <= cutoffTime)
			{
				fs::remove(file);
			}
		}
	}
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
	if (protection) {
		for (auto& folder : forbiddenFolders)
		{
			int start = path.find(folder);		
			if (start == 0) {
				throw(std::invalid_argument("wrong directory"));
			}			
		}
	}	
	getSortedFilesByTime();
	clean();
}

Cleaner::~Cleaner()
{

}

void Cleaner::clean()
{	
	if (daysToStore!=0) {
		cleanByAge();
	}
	if (countFiles != 0) {
		cleanByCount();
	}
	if (sizeOFolder != 0) {
		cleanByFolderSize();
		
	}
}
