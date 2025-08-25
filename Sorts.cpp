#include "Sorts.h"

int findMinIndexGood(FILE* file, int start, int end, int option, bool ascendingOrder) {
    Good min;
    int minIndex = start;
    fseek(file, start * sizeof(Good), SEEK_SET);
    fread(&min, sizeof(Good), 1, file);

    for (int i = start + 1; i <= end; ++i) {
        fseek(file, i * sizeof(Good), SEEK_SET);
        Good current;
        fread(&current, sizeof(Good), 1, file);

        switch (option)
        {
        case 1:
            if (ascendingOrder)
            {
                if (current.id < min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.id > min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 2:
            if (ascendingOrder)
            {
                if (compareDates(current.name, min.name)) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (!compareDates(current.name, min.name)) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 3:
            if (ascendingOrder)
            {
                if (strcmp(current.description, min.description) < 0) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (strcmp(current.description, min.description) > 0) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 4:
            if (ascendingOrder)
            {
                if (current.value < min.value) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.value > min.value) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 5:
            if (ascendingOrder)
            {
                if (strcmp(getCategoryName(current.idCategory), getCategoryName(min.idCategory)) < 0) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (strcmp(getCategoryName(current.idCategory), getCategoryName(min.idCategory)) > 0) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        }
    }
    return minIndex;
}

int findMinIndexOrder(FILE* file, int start, int end, int option, bool ascendingOrder)
{
    Order min;
    int minIndex = start;
    fseek(file, start * sizeof(Order), SEEK_SET);
    fread(&min, sizeof(Order), 1, file);

    for (int i = start + 1; i <= end; ++i) {
        fseek(file, i * sizeof(Order), SEEK_SET);
        Order current;
        fread(&current, sizeof(Order), 1, file);

        switch (option)
        {
        case 1:
            if (ascendingOrder)
            {
                if (current.id < min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.id > min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 2:
            if (ascendingOrder)
            {
                if (compareDates(current.date, min.date)) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (!compareDates(current.date, min.date)) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 3:
            if (ascendingOrder)
            {
                if (current.value < min.value) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.value > min.value) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 4:
            if (ascendingOrder)
            {
                if (current.status < min.status) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.status > min.status) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 5:
            if (ascendingOrder)
            {
                if (current.numGoods < min.numGoods) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.numGoods > min.numGoods) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        }
    }
    return minIndex;
}

int findMinIndexUsers(FILE* file, int start, int end, int option, bool ascendingOrder)
{
    User min;
    int minIndex = start;
    fseek(file, start * sizeof(User), SEEK_SET);
    fread(&min, sizeof(User), 1, file);

    for (int i = start + 1; i <= end; ++i) {
        fseek(file, i * sizeof(User), SEEK_SET);
        User current;
        fread(&current, sizeof(User), 1, file);

        switch (option)
        {
        case 1:
            if (ascendingOrder)
            {
                if (current.id < min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.id > min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 2:
            if (ascendingOrder)
            {
                if (compareDates(current.phoneNumber, min.phoneNumber)) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (!compareDates(current.phoneNumber, min.phoneNumber)) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 3:
            if (ascendingOrder)
            {
                if (strcmp(current.email, min.email) < 0) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (strcmp(current.email, min.email) > 0) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 4:
            if (ascendingOrder)
            {
                if (current.balance < min.balance) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.balance > min.balance) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 5:
            if (ascendingOrder)
            {
                if (getBonusCard(current.id, NULL).value < getBonusCard(min.id, NULL).value) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (getBonusCard(current.id, NULL).value > getBonusCard(min.id, NULL).value) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        }
    }
    return minIndex;
}

int findMinIndexBonusCard(FILE* file, int start, int end, int option, bool ascendingOrder)
{
    BonusCard min;
    int minIndex = start;
    fseek(file, start * sizeof(BonusCard), SEEK_SET);
    fread(&min, sizeof(BonusCard), 1, file);

    for (int i = start + 1; i <= end; ++i) {
        fseek(file, i * sizeof(BonusCard), SEEK_SET);
        BonusCard current;
        fread(&current, sizeof(BonusCard), 1, file);

        switch (option)
        {
        case 1:
            if (ascendingOrder)
            {
                if (current.id < min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.id > min.id) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 2:
            if (ascendingOrder)
            {
                if (current.value < min.value) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.value > min.value) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        case 3:
            if (ascendingOrder)
            {
                if (current.percent < min.percent) {
                    minIndex = i;
                    min = current;
                }
            }
            else
            {
                if (current.percent > min.percent) {
                    minIndex = i;
                    min = current;
                }
            }
            break;
        }
    }
    return minIndex;
}



void swap(FILE* file, int i, int j, int size) {
    void* buffer1 = malloc(size);
    void* buffer2 = malloc(size);

    if (!buffer1 || !buffer2) {
        cout << "Ошибка выделения памяти\n";
        free(buffer1);
        free(buffer2);
        return;
    }

    fseek(file, i * size, SEEK_SET);
    fread(buffer1, size, 1, file);

    fseek(file, j * size, SEEK_SET);
    fread(buffer2, size, 1, file);

    fseek(file, i * size, SEEK_SET);
    fwrite(buffer2, size, 1, file);

    fseek(file, j * size, SEEK_SET);
    fwrite(buffer1, size, 1, file);

    free(buffer1);
    free(buffer2);
}
//typeStruct:
//Good - 1 
//Order - 2
//Users - 3
//BonusCard - 4
void selectionSort(const char* filename, int option, int structSize, int typeStruct, bool ascendingOrder) {

    int value = getCountStructsInFile(filename, structSize);
    FILE* file = fopen(filename, "rb+");

    if (!file) {
        cout << "Ошибка открытия файла";
        return;
    }
    for (int i = 0; i < value - 1; ++i) {
        int minIndex = 0;
        switch (typeStruct) {
        case 1:
            minIndex = findMinIndexGood(file, i, value - 1, option, ascendingOrder);
            break;
        case 2:
            minIndex = findMinIndexOrder(file, i, value - 1, option, ascendingOrder);
            break;
        case 3:
            minIndex = findMinIndexUsers(file, i, value - 1, option, ascendingOrder);
            break;
        case 4:
            minIndex = findMinIndexBonusCard(file, i, value - 1, option, ascendingOrder);
            break;
        }

        if (minIndex != i) {
            swap(file, i, minIndex, structSize);
        }
    }
    fclose(file);
}