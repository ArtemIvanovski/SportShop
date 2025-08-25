#pragma once
#include "CategoryWindow.h"
#include "GoodWindow.h"


int showLogIn();
void showSignUp();

void showProfile(User user, Data data, BonusCard bonuscard, bool isUser);
void showChangePassword(Data data, int position);
void showChangeProfile(User* user, Data* data, BonusCard bonuscard, int positionUser, int positionData);


void showUserPanel(int id);
void showInputBalance(User* user, int positionUser);


void showManipulationOfOrdersUser(int id);
void showCancelOrder(int id);
void showAndSortOrders(int id);
void showOrders(int id);
void showAddOrder(int id);
void showChangeStatusOrder();
void showManipulationOfOrder();

void showBonusOrderHistory(int id);

void showAdminPanel(int id);


void showUsers(int id);
void showAndSortUsers(int id);
void showFindUser(int id);

void showAllInformationUser(int id);
void showManipulationOfBonusCard();


void showManipulationOfBlocks(int id);
void showAddBlock(int id);
void showBlocks();
void showRemoveBlock();

void showBonusCards();
void showAndSortBonusCard();
void showFindBonusCard();
void showBonusCardInformation();
void showChangePercentBonusCard();
