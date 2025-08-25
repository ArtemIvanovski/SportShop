#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <io.h>
#include <locale.h>            
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

using namespace std;

#define FILENAME_DATA "Data.bin"
#define FILENAME_USERS "Users.bin"
#define FILENAME_BLOCKS "Blocks.bin"
#define FILENAME_CATEGORIES "Categories.bin"
#define FILENAME_GOODS "Goods.bin"
#define FILENAME_BONUS_CARDS "BonusCards.bin"
#define FILENAME_BONUS_ORDERS "BonusOrders.bin"
#define FILENAME_ORDERS "Orders.bin"
#define MAX_INPUT_SIZE 100


#define AUTHORIZATION_MENU "�����������\n1. �����\n2. ������������������\n0. ����� �� ���������\n"
#define USER_PANEL_MENU "1. �������� �������\n2. �������� ������� �� ����������\n3. ����� ������\n4. ������ ������\n5. �������� �������\n6. ����������� � ��������\n7. ���������� ������� ���������� �������� ������\n0. �����\n"
#define MANIPULATION_CATEGORY_MENU "1. ����������� ���������\n2. �������� ���������\n3. ������� ���������\n4. �������� ���������\n0. �����\n"
#define MANIPULATION_GOOD_MENU "1. �������� �����\n2. ������� �����\n3. ����� ������\n4. �������� ������\n5. �������� �����\n6. ������� ������ �� ����������\n0. �����\n"
#define CHANGE_PROFILE_MENU "�������� ��� ������ ��������?\n1. ����� ��������\n2. �������� �����\n3. �����\n4. ������\n5. ��������� ���������\n0. �����\n"

#define GOOD_SORT_MENU "�������� �������� �� �������� ����� ���������� ����������\n(��� ����� ������� ���������� �� �����������\n��� ������� ������� ���������� �� ��������):\n1. �� ID\n2. �� ��������\n3. �� ��������\n4. �� ���������\n5. �� ����������"
#define ORDER_SORT_MENU "�������� �������� �� �������� ����� ���������� ����������\n(��� ����� ������� ���������� �� �����������\n��� ������� ������� ���������� �� ��������):\n1. �� ID\n2. �� ����\n3. �� ���������\n4. �� �������\n5. �� ���������� �������"
#define USER_SORT_MENU "�������� �������� �� �������� ����� ���������� ����������\n(��� ����� ������� ���������� �� �����������\n��� ������� ������� ���������� �� ��������):\n1. �� ID\n2. �� ������ ��������\n3. �� ��������� ������\n4. �� �������\n5. �� ������� �������\n"
#define BONUS_CARD_SORT_MENU "�������� �������� �� �������� ����� ���������� ����������\n(��� ����� ������� ���������� �� �����������\n��� ������� ������� ���������� �� ��������):\n1. �� ID\n2. �� ���������� �������\n3. �� ��������\n"

#define USER_MANIPULATION_ORDER_MENU "1. �������� �����\n2. �������� �����\n3. �������� �������\n0. �����\n"

#define GOOD_CHANGE_MENU "�������� ��� ������ ��������?\n1. ��������� ������\n2. �������� ������\n3. �������� ������\n4. ���������\n5. ��������� ���������\n0. �����\n"
#define ADMIN_PANEL_MENU "1. �������� �������������\n2. ����������� � ������������\n3. �������� ���� ���������� � ������������\n4. ����� ������������\n5. ����������� � �����������\n6. ����������� � ��������\n7. ����������� �� ��������\n8. ����������� � ��������� �������\n0. �����\n"
#define MANIPULATION_BLOCKS_MENU "1. �������� ����������\n2. ����� ����������\n3. �������� ��� ����������\n0. �����\n"
#define MANIPULATION_ORDERS_MENU "1. �������� ������ ������\n2. �������� ���� ������\n0. �����\n"
#define MANIPULATION_BONUS_CARD_MENU "1. ����� �������� �����\n2. �������� ���� �������� ����\n3. �������� ���������� ���� �������\n4. �������� ���������� ������� ��� ������������ �����\n5. �������� ������� ���������� �������\n0. �����\n"


struct Data {
	char login[20];
	char password[20];
	int id;
	int role;
};

struct User {
	int id;
	char phoneNumber[14];
	char email[30];
	double balance;
};

struct BonusCard {
	int id;
	int value;
	double percent;
};

struct BonusOrder {
	int id;
	int idBonusCard;
	int value;
	int idOrder;
	char date[11];
};

struct Block {
	int id;
	int idUser;
	char reason[20];
	char dateLockWasLifted[11];
};

struct Category {
	char name[30];
	int id;
};

struct Good {
	char name[30];
	char description[40];
	int id;
	double value;
	int idCategory;
};

struct Order {
	int id;
	char date[11];
	double value;
	int idUser;
	int status;// 1 - �� ������������, 2 - ��������, 3 - �������, 4 - �� ������� 
	int goodIDs[99];
	int numGoods;
};
