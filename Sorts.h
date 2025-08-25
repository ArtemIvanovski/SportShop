#pragma once
#include "FileFunction.h"
#include "OtherFunction.h"

void selectionSort(const char* filename, int option, int structSize, int typeStruct, bool ascendingOrder);
void swap(FILE* file, int i, int j, int size);
int findMinIndexGood(FILE* file, int start, int end, int option, bool ascendingOrder);
int findMinIndexOrder(FILE* file, int start, int end, int option, bool ascendingOrder);
int findMinIndexUsers(FILE* file, int start, int end, int option, bool ascendingOrder);
int findMinIndexBonusCard(FILE* file, int start, int end, int option, bool ascendingOrder);