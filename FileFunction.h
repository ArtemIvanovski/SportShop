#pragma once
#include "Libraries.h"

int getCountStructsInFile(const char* filename, int structSize);
void readStructFromFile(const char* filename, int structSize, int position, void* result);
void removeStructFromFile(const char* filename, int structSize, int position);
void writeStructToFile(const char* filename, const void* data, int dataSize, int position);

