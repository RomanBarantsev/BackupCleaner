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
	loadFromFile("StoreData.dat");
}

 StoreData::~StoreData() {
     //saveToFile("StoreData.dat");
     for (auto& folder : Folders)
     {
         delete folder.second;
         folder.second = nullptr;
     }
}

const std::unordered_map<std::string, FolderData*> StoreData::GetData()
{
    return Folders;
}

bool StoreData::deleteFolder(std::string Folder)
{
    if (Folders.erase(Folder) != 0)
        return true;
    return false;
}

void StoreData::addFolder(std::string path, FolderData*& folder)
{
    if(folder == nullptr)
        folder = new FolderData(0, 0, 0);
    Folders.emplace(path,folder);
}

bool StoreData::findByKey(std::string key)
{
    if (Folders.find(key)!=Folders.end()) {
        return true;
    }
    return false;
}

