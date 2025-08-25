#include "Menu.h"

int menu(string caption, int board) {
    char choice;
    int numericChoice;

    do {
        cout << caption;
        choice = _getch();
        if (choice == 27) {
            numericChoice = 0;
        }
        else if (choice >= '0' && choice <= char('0' + board)) {
            numericChoice = choice - '0';
        }
        else {
            numericChoice = -1;
        }
    } while (numericChoice < 0 || numericChoice > board + 1);

    return numericChoice;
}
