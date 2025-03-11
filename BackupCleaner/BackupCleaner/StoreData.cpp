#include "StoreData.h"

 void StoreData::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write((char*)this, sizeof(FolderData));
        file.close();
    }
}

 void StoreData::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read((char*)this, sizeof(FolderData));
        file.close();
    }
}

 StoreData::StoreData() {
	//loadFromFile("StoreData.dat");
}

 StoreData::~StoreData() {
	//saveToFile("StoreData.dat");
}

const std::unordered_map<std::string, FolderData> StoreData::GetData()
{
    return Folders;
}

bool StoreData::deleteFolder(std::string Folder)
{
    if (Folders.erase(Folder) != 0)
        return true;
    return false;
}

void StoreData::addFolder(std::string path,FolderData folder)
{
    Folders.emplace(path,folder);
}

