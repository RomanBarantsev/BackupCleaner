#pragma once
#include "FolderData.h"
#include <fstream>
#include <unordered_map>

class StoreData
{
private:
	std::unordered_map<std::string,FolderData&> Folders;
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
private:
	public:
		StoreData();
		~StoreData();
		const std::unordered_map<std::string,FolderData&> GetData();
		bool deleteFolder(std::string Folder);
		void addFolder(std::string path, FolderData& folder);
		bool findByKey(std::string key);
};

