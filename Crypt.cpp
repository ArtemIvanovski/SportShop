#include "Crypt.h"

void encrypt(char* data, int key) {
    int i;
    int len = strlen(data);
    for (i = 0; i < len; i++) {
        data[i] = data[i] + key;
    }
}
