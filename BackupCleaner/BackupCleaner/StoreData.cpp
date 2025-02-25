#include "StoreData.h"

inline void StoreData::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write((char*)this, sizeof(FolderData));
        file.close();
    }
}

inline void StoreData::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read((char*)this, sizeof(FolderData));
        file.close();
    }
}

inline StoreData::StoreData() {
	loadFromFile("StoreData.dat");
}

inline StoreData::~StoreData() {
	saveToFile("StoreData.dat");
}
