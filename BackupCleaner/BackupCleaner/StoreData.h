#pragma once
#include <vector>
#include "FolderData.h"
#include <fstream>

class StoreData
{
    void saveToFile(const std::string& filename);

    void loadFromFile(const std::string& filename);
private:
	std::vector<FolderData> Folders;
	public:
		StoreData();
		~StoreData();
};

