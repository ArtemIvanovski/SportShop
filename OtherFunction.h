#pragma once
#include "Libraries.h"
#include "FileFunction.h"

bool isValidPassword(const char* password);
bool isValidPhoneNumber(const char* phoneNumber);
bool delayPress();
void rusActivate();
char* intToString(int num);
char* toLower(const char* str);
char* doubleToString(double num);
bool isValidDate(const char* dateChar);
bool compareDates(char* date1, char* date2);
char* getCurrentDate();
bool isValidEmail(const char* email);
Block isBlockUser(int idUser);
void unblockUsers();
Data getData(int id, int* position);
User getUser(int id, int* position);
Good getGood(int id);
BonusCard getBonusCard(int id, int* position);
int isIdExists(int* array, int size, int id);
int getUniqueUserId();
int getUniqueBlockId();
int getUniqueGoodId();
int getUniqueBonusOrderId();
int getUniqueOrderId();
int getUniqueCategoryId();
char* getCategoryName(int categoryId);

void showCategory(Category category);
void showCaptionCategory();
void showBoardCategory();

void showBoardGood();
void showCaptionGood();
void showGood(Good good);

void showBoardOrder();
void showCaptionOrder();
void showOrder(Order order);

void showUser(User user);
void showCaptionUser();
void showBoardUser();

void showBlock(Block block);
void showCaptionBlock();
void showBoardBlock();

void showBoardBonusOrder(int id);
void showCaptionBonusOrder(int id);
void showBonusOrder(BonusOrder bonusOrder, int id);

void showBoardBonusCard();
void showCaptionBonusCard();
void showBonusCard(BonusCard bonusCard);