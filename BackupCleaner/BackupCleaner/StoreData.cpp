#include "StoreData.h"

void StoreData::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    size_t size = Folders.size();
    file.write((char*)&size, sizeof(size_t));  // count of folders

    for (const auto& pair : Folders) {
        size_t pathSize = pair.first.size();
        file.write((char*)&pathSize, sizeof(size_t));  // path lenght
        file.write(pair.first.c_str(), pathSize);      // path itself

        file.write((char*)&pair.second->daysToStore, sizeof(int));
        file.write((char*)&pair.second->folderSize, sizeof(int));
        file.write((char*)&pair.second->countFiles, sizeof(int));
    }

    file.close();
}

void StoreData::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    size_t size;
    file.read((char*)&size, sizeof(size_t));  // reading how many folders are
    if (size == SIZE_MAX)
        return;
    for (size_t i = 0; i < size; i++) {
        size_t pathSize;
        file.read((char*)&pathSize, sizeof(size_t));  // reading length of path

        std::string path(pathSize, '\0');
        file.read(&path[0], pathSize);  // reading path

        int daysToStore, folderSize, countFiles;
        file.read((char*)&daysToStore, sizeof(int));
        file.read((char*)&folderSize, sizeof(int));
        file.read((char*)&countFiles, sizeof(int));

        Folders[path] = new FolderData(daysToStore, folderSize, countFiles);
    }

    file.close();
}

 StoreData::StoreData() {
     try {
         loadFromFile(fileName);
     }
     catch (std::exception) {
         namespace fs = std::filesystem;
         fs::path filePath = fs::current_path() / fileName;
         if (fs::exists(filePath)) {
             fs::remove(filePath);
         }
     }
}

 StoreData::~StoreData() {
    saveToFile("StoreData.dat");
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

