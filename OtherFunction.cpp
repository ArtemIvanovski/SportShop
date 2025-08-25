#include "OtherFunction.h"

bool isValidPassword(const char* password) {
    if (strlen(password) < 8) {
        return false;
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (int i = 0; password[i] != '\0'; i++) {
        if (isalpha(password[i])) {
            hasLetter = true;
        }
        if (isdigit(password[i])) {
            hasDigit = true;
        }
    }

    return hasLetter && hasDigit;
}

void rusActivate()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
}

bool delayPress() {
    char ch;
    while ((ch = _getch()) != 27) {
        if (ch == 13) {
            return true;
        }
    }
    return false;
}

bool isValidPhoneNumber(const char* phoneNumber) {
    if (strlen(phoneNumber) != 13) {
        return false;
    }

    if (phoneNumber[0] != '+') {
        return false;
    }

    char countryCode[4];
    strncpy(countryCode, phoneNumber + 1, 3);
    countryCode[3] = '\0';
    if (strcmp(countryCode, "375") != 0) {
        return false;
    }

    char operatorCode[3];
    strncpy(operatorCode, phoneNumber + 4, 2);
    operatorCode[2] = '\0';
    if (strcmp(operatorCode, "44") != 0 &&
        strcmp(operatorCode, "25") != 0 &&
        strcmp(operatorCode, "33") != 0 &&
        strcmp(operatorCode, "29") != 0) {
        return false;
    }

    const char* remainingDigits = phoneNumber + 6;

    while (*remainingDigits) {
        if (!isdigit(*remainingDigits)) {
            return false;
        }
        remainingDigits++;
    }

    return true;
}

char* intToString(int num) {
    int len = snprintf(NULL, 0, "%d", num) + 1;
    char* str = new char[len];
    if (!str) {
        cout << "Ошибка выделения памяти";
        exit(EXIT_FAILURE);
    }
    snprintf(str, len, "%d", num);
    return str;
}

char* doubleToString(double num) {
    int len = snprintf(NULL, 0, "%.2f", num) + 1;
    char* str = new char[len];
    if (!str) {
        cout << "Ошибка выделения памяти";
        exit(EXIT_FAILURE);
    }
    snprintf(str, len, "%.2f", num);
    return str;
}

char* toLower(const char* str) {
    int len = strlen(str);
    char* result = new char[len];
    if (!result) {
        cout << "Ошибка выделения памяти";
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < len; i++) {
        result[i] = tolower(str[i]);
    }
    result[len] = '\0';

    return result;
}

bool isValidDate(const char* dateChar) {
    string date(dateChar);
    if (date.length() != 10) {
        return false;
    }
    if (date[2] != '.' || date[5] != '.') {
        return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) {
                return false;
            }
        }
        else {
            if (day > 28) {
                return false;
            }
        }
    }

    return true;
}

bool compareDates(char* date1, char* date2) {
    int year1, month1, day1;
    int year2, month2, day2;
    sscanf(date1, "%d.%d.%d", &day1, &month1, &year1);
    sscanf(date2, "%d.%d.%d", &day2, &month2, &year2);
    
    if (year1 < year2) {
        return true;
    }
    else if (year1 > year2) {
        return false;
    }

    if (month1 < month2) {
        return true;
    }
    else if (month1 > month2) {
        return false;
    }

    if (day1 < day2) {
        return true;
    }

    return false;
}

char* getCurrentDate() {
    time_t currentTime;
    struct tm* timeInfo;
    char* buffer = new char[11]; 

    time(&currentTime);
    timeInfo = localtime(&currentTime);

    strftime(buffer, 11, "%d.%m.%Y", timeInfo);

    return buffer;
}

bool isValidEmail(const char* email) {
    string emailStr(email);

    size_t atPos = emailStr.find('@');
    if (atPos == string::npos) {
        return false; 
    }

    for (size_t i = 0; i < atPos; ++i) {
        if (!isalnum(emailStr[i]) && emailStr[i] != '.') {
            return false; 
        }
    }

    string domain = emailStr.substr(atPos + 1);

    if (domain == "mail.ru" || domain == "gmail.com" || domain == "yandex.ru" ) {
        return true;
    }

    return false; 
}

Block isBlockUser(int idUser) {
    int value = getCountStructsInFile(FILENAME_BLOCKS, sizeof(Block));

    Block data{};

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_BLOCKS, sizeof(Block), i, &data);

        if (data.idUser == idUser)
        {
            return data;
        }
    }

    data.id = -1;

    return data;
}

void unblockUsers() {
    int value = getCountStructsInFile(FILENAME_BLOCKS, sizeof(Block));
    int* positions = new int[value];
    int size = 0;
    char* date = getCurrentDate();

    Block data{};

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_BLOCKS, sizeof(Block), i, &data);

        if (compareDates(data.dateLockWasLifted, date))
        {
            positions[size] = i;
            size++;
        }
    }

    for (int i = 0; i < size; i++)
    {
        removeStructFromFile(FILENAME_BLOCKS, sizeof(Block), positions[i]);
    }
}

User getUser(int id, int* position) {
    int value = getCountStructsInFile(FILENAME_USERS, sizeof(User));

    User user{};
    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_USERS, sizeof(User), i, &user);
        if (user.id == id) {
            *position = i;
            return user;
        }
    }
    user.id = -1;

    return user;
}

BonusCard getBonusCard(int id, int* position) {
    int value = getCountStructsInFile(FILENAME_BONUS_CARDS, sizeof(BonusCard));

    BonusCard bonusCard{};

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_BONUS_CARDS, sizeof(BonusCard), i, &bonusCard);
        if (bonusCard.id == id) {
            *position = i;
            return bonusCard;
        }
    }
    bonusCard.id = -1;

    return bonusCard;
}

Good getGood(int id) {
    int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));

    Good good{};

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_GOODS, sizeof(Good), i, &good);
        if (good.id == id)
            return good;
    }
    good.id = -1;

    return good;
}

Data getData(int id, int* position) {
    int value = getCountStructsInFile(FILENAME_DATA, sizeof(Data));

    Data data{};

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_DATA, sizeof(Data), i, &data);
        if (data.id == id) {
            *position = i;
            return data;
        }
    }
    data.id = -1;

    return data;
}

int getUniqueUserId()
{
    int value = getCountStructsInFile(FILENAME_USERS, sizeof(struct User));

    int* arrayId = new int[value];
    int index = 0;
    User user;

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_USERS, sizeof(struct User), i, &user);
        arrayId[index] = user.id;
        index++;
    }

    int id;
    srand(time(NULL));
    do {
        id = rand() % 10000 + 1;
    } while (isIdExists(arrayId, value, id));

    free(arrayId);
    return id;
}

int getUniqueBlockId()
{
    int value = getCountStructsInFile(FILENAME_BLOCKS, sizeof(Block));

    int* arrayId = new int[value];
    int index = 0;
    Block block;

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_BLOCKS, sizeof(Block), i, &block);
        arrayId[index] = block.id;
        index++;
    }

    int id;
    srand(time(NULL));
    do {
        id = rand() % 10000 + 1;
    } while (isIdExists(arrayId, value, id));

    free(arrayId);
    return id;
}

int getUniqueGoodId()
{
    int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));

    int* arrayId = new int[value];
    int index = 0;
    Good good;

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_GOODS, sizeof(Good), i, &good);
        arrayId[index] = good.id;
        index++;
    }

    int id;
    srand(time(NULL));
    do {
        id = rand() % 10000 + 1;
    } while (isIdExists(arrayId, value, id));

    free(arrayId);
    return id;
}

int getUniqueBonusOrderId()
{
    int value = getCountStructsInFile(FILENAME_BONUS_ORDERS, sizeof(BonusOrder));

    int* arrayId = new int[value];
    int index = 0;
    BonusOrder bonusOrder;

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_BONUS_ORDERS, sizeof(BonusOrder), i, &bonusOrder);
        arrayId[index] = bonusOrder.id;
        index++;
    }

    int id;
    srand(time(NULL));
    do {
        id = rand() % 10000 + 1;
    } while (isIdExists(arrayId, value, id));

    free(arrayId);
    return id;
}

int getUniqueOrderId()
{
    int value = getCountStructsInFile(FILENAME_ORDERS, sizeof(Order));

    int* arrayId = new int[value];
    int index = 0;
    Order order;

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);
        arrayId[index] = order.id;
        index++;
    }

    int id;
    srand(time(NULL));
    do {
        id = rand() % 10000 + 1;
    } while (isIdExists(arrayId, value, id));

    free(arrayId);
    return id;
}

int getUniqueCategoryId()
{
    int value = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));

    int* arrayId = new int[value];
    int index = 0;
    Category category;

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);
        arrayId[index] = category.id;
        index++;
    }

    int id;
    srand(time(NULL));
    do {
        id = rand() % 10000 + 1;
    } while (isIdExists(arrayId, value, id));

    free(arrayId);
    return id;
}

int isIdExists(int* array, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (array[i] == id) {
            return 1;
        }
    }
    return 0;
}

char* getCategoryName(int categoryId) {
    char* name = new char[30];
    int value = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));

    Category category{};

    for (int i = 0; i < value; i++)
    {
        readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);
        if (category.id == categoryId)
        {
            strcpy(name, category.name);
            return name;

        }
    }
}

void showCategory(Category category)
{
    cout << "| " << setw(10) << category.id << " | " << setw(30) << category.name << " |" << endl;
}

void showCaptionCategory()
{
    cout << "|" << setw(11) << "ID" << " |" << setw(31) << "Название категории" << " |" << endl;
}

void showBoardCategory()
{
    cout << "|------------|--------------------------------|" << std::endl;
}



void showGood(Good good) {
    cout << "| " << setw(10) << left << good.id << "| "
        << setw(30) << good.name << "| "
        << setw(40) << good.description << "| "
        << setw(10) << good.value << "| "
        << setw(30) << getCategoryName(good.idCategory) << "|" << endl;
}

void showCaptionGood() {
    cout << "| " << setw(10) << left << "ID" << "| "
        << setw(30) << "Название" << "| "
        << setw(40) << "Описание" << "| "
        << setw(10) << "Цена" << "| "
        << setw(30) << "Название категории" << "|" << endl;
}

void showBoardGood() {
    cout << "|-----------|-------------------------------|-----------------------------------------|-----------|-------------------------------|" << endl;
}


void showOrder(Order order) {
    cout << endl;
    showBoardOrder();
    showCaptionOrder();
    showBoardOrder();
    string statusStr;
    Good good{};
    if (order.status == 1)
        statusStr = "на рассмотрении";
    else if (order.status == 2)
        statusStr = "выполнен";
    else if (order.status == 3)
        statusStr = "отменен";
    else if (order.status == 4)
        statusStr = "не одобрен";

    cout << "| " << setw(5) << order.id << " | "
        << setw(10) << order.date << " | "
        << setw(10) << fixed << setprecision(2) << order.value << " | "
        << setw(6) << order.idUser << " | "
        << setw(15) << statusStr << " | "
        << setw(18) << order.numGoods << " | " << endl;

    showBoardOrder();

    cout << endl << "Товары:" << endl;
    showBoardGood();
    showCaptionGood();
    showBoardGood();

    for (int i = 0; i < order.numGoods; i++)
    {
        good = getGood(order.goodIDs[i]);
        if (good.id == -1)
        {
            cout << "Товар удален" << endl;
        }
        showGood(good);
    }

    showBoardGood();
}

void showCaptionOrder() {
    cout << "| ID    | Дата       | Сумма      | IDUser | Статус          | Количество товаров |" << endl;
}

void showBoardOrder() {
    cout << "|-------|------------|------------|--------|-----------------|--------------------|" << endl;
}



void showUser(User user)
{
    int position;
    int value = getBonusCard(user.id, &position).value;
    double percent = getBonusCard(user.id, &position).percent;
    cout << "| " << setw(5) << user.id << " | "
        << setw(14) << user.phoneNumber << " | "
        << setw(28) << user.email << " | "
        << fixed << setprecision(2) << std::setw(9) << user.balance << " | "
        << setw(7) << value << " | "
        << setw(9) << fixed << setprecision(2) << percent << " |" << endl;
}

void showCaptionUser()
{
    cout << "| ID    | Номер телефона | Почтовый адрес               | Баланс    | Бонусы  | Процент   |" << endl;
}

void showBoardUser()
{
    cout << "|-------|----------------|------------------------------|-----------|---------|-----------|" << endl;
}




void showBlock(Block block)
{
    cout << "| " << setw(5) << block.id << " | ";
    cout << setw(15) << block.idUser << " | ";
    cout << setw(16) << block.reason << " | ";
    cout << setw(20) << block.dateLockWasLifted << " |" << endl;
}

void showCaptionBlock()
{
    cout << "| ID    | Id пользователя | Причина          | Дата разблокирования |" << endl;
}

void showBoardBlock()
{
    cout << "|-------|-----------------|------------------|----------------------|" << endl;
}


void showBonusOrder(BonusOrder bonusOrder, int id) {
    cout << "| " << setw(5) << bonusOrder.id << " | ";
    if (id == -1) {
        cout << setw(17) << bonusOrder.idBonusCard << " | ";
    }
    cout << setw(7) << bonusOrder.value << " | "
        << setw(9) << bonusOrder.idOrder << " | "
        << setw(10) << bonusOrder.date << " |" << endl;
}

void showCaptionBonusOrder(int id) {
    cout << "| ID    | ";
    if (id == -1)
    {
        cout << "ID бонусной карты | ";
    }
    cout << "Сумма   | ";
    cout << "ID заказа | ";
    cout << "Дата       |" << endl;
}

void showBoardBonusOrder(int id) {
    if (id == -1)
    {
        cout << "|-------|-------------------|---------|-----------|------------|" << endl;
    }
    else
    {
        cout << "|-------|---------|-----------|------------|" << endl;
    }
}


void showBonusCard(BonusCard bonusCard) {
    cout << "| " << setw(5) << bonusCard.id << " | "
        << setw(18) << bonusCard.value << " | "
        << setw(9) << fixed << setprecision(2) << bonusCard.percent << " |" << endl;
}

void showCaptionBonusCard() {
    cout << "| ID    | Количество бонусов | Процент   |" << endl;
}

void showBoardBonusCard() {
    cout << "|-------|--------------------|-----------|" << endl;
}
