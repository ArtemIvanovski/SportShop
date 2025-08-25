#include "FileFunction.h"

int getCountStructsInFile(const char* filename, int structSize) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return 0;
    }

    file.seekg(0, ios::end);
    long fileSize = file.tellg();
    file.seekg(0, ios::beg);

    int count = fileSize / structSize;

    file.close();
    return count;
}

void readStructFromFile(const char* filename, int structSize, int position, void* result) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    file.seekg(position * structSize, ios::beg);
    file.read((char*)(result), structSize);

    file.close();
}

void removeStructFromFile(const char* filename, int structSize, int position) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    file.seekg(0, ios::end);
    long fileSize = file.tellg();
    int numStructs = fileSize / structSize;

    if (position >= numStructs || position < 0) {
        cout << "Позиция для удаления находится за пределами файла" << endl;
        file.close();
        return;
    }

    file.seekg((position + 1) * structSize, ios::beg);

    for (int i = position + 1; i < numStructs; i++) {
        file.seekg(i * structSize, ios::beg);
        char* buffer = new char[structSize];
        file.read(buffer, structSize);

        file.seekp((i - 1) * structSize, ios::beg);
        file.write(buffer, structSize);

        delete[] buffer;
    }

    int newSize = (numStructs - 1) * structSize;
    file.close();

    filesystem::resize_file(filename, newSize);
}

void writeStructToFile(const char* filename, const void* data, int dataSize, int position) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        return;
    }

    if (position != -1) {
        file.seekp(position * dataSize, ios::beg);
    }
    else {
        file.seekp(0, ios::end); 
    }

    file.write((const char*)(data), dataSize);

    file.close();
}

