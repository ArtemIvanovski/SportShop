#include "Input.h"

char* getInput(bool isPassword) {
    char* input = new char[MAX_INPUT_SIZE];

    char ch;
    int len = 0;
    while ((ch = _getch()) != 13) {
        if (ch == 27) {
            return NULL;
        }
        if (ch == 8 && len > 0) {
            len--;
            input[len] = '\0';
            cout << "\b \b";
        }
        else {
            if (isPassword) {
                cout << "*";
            }
            else {
                cout << ch;
            }

            input[len] = ch;
            len++;
            input[len] = '\0';
        }
    }

    if (len == 0)
    {
        input[len] = '\0';
    }

    cout << endl;
    return input;
}
int getInputInt() {
    char input[MAX_INPUT_SIZE];
    int len = 0;
    char ch;

    while ((ch = _getch()) != 13) {
        if (ch == 27) {
            return -1;
        }

        if (ch == 9)
        {
            return -99;
        }

        if (ch >= '0' && ch <= '9' && len < MAX_INPUT_SIZE - 1) {
            cout << ch;
            input[len] = ch;
            len++;
        }
        else if (ch == 8 && len > 0) {
            len--;
            cout << "\b \b";
        }
    }

    input[len] = '\0';
    cout << endl;
    if (len == 0) {
        return -2;
    }
    int number = atoi(input);
    return (number < 0) ? -2 : number;
}

double getInputDouble() {
    char input[MAX_INPUT_SIZE];
    int len = 0;
    char ch;
    int dotCount = 0;

    while ((ch = _getch()) != 13) {
        if (ch == 27) {
            return -1.0;
        }
        if ((ch >= '0' && ch <= '9' && len < MAX_INPUT_SIZE - 1) || (ch == ',' && dotCount == 0 && len < MAX_INPUT_SIZE - 2)) {
            cout << ch;
            input[len] = ch;
            len++;
            if (ch == ',') {
                dotCount++;
            }
        }
        else if (ch == 8 && len > 0) {
            len--;
            if (input[len] == '.') {
                dotCount--;
            }
            cout << "\b \b";
        }
    }

    input[len] = '\0';
    cout << endl;
    if (len == 0 || dotCount > 1) {
        return -2.0;
    }
    char* endPtr;
    double number = strtod(input, &endPtr);
    return (number < 0) ? -2 : number;
}