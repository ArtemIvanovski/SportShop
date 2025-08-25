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


#define AUTHORIZATION_MENU "Авторизация\n1. Войти\n2. Зарегистрироваться\n0. Выход из программы\n"
#define USER_PANEL_MENU "1. Просмотр товаров\n2. Просмотр товаров по категориям\n3. Поиск товара\n4. Внести деньги\n5. Изменить профиль\n6. Манипуляции с заказами\n7. Посмотреть историю начисления бонусных баллов\n0. Выйти\n"
#define MANIPULATION_CATEGORY_MENU "1. Просмотреть категории\n2. Изменить категорию\n3. Удалить категорию\n4. Добавить категорию\n0. Выйти\n"
#define MANIPULATION_GOOD_MENU "1. Добавить товар\n2. Удалить товар\n3. Поиск товара\n4. Показать товары\n5. Изменить товар\n6. Вывести товары по категориям\n0. Выйти\n"
#define CHANGE_PROFILE_MENU "Выберите что хотите изменить?\n1. Номер телефона\n2. Почтовый адрес\n3. Логин\n4. Пароль\n5. Сохранить изменения\n0. Выйти\n"

#define GOOD_SORT_MENU "Выберите параметр по которому нужно произвести сортировку\n(при одном нажатии сортировка по возрастанию\nпри двойном нажатии сортировка по убыванию):\n1. По ID\n2. По названию\n3. По описанию\n4. По стоимости\n5. По категориям"
#define ORDER_SORT_MENU "Выберите параметр по которому нужно произвести сортировку\n(при одном нажатии сортировка по возрастанию\nпри двойном нажатии сортировка по убыванию):\n1. По ID\n2. По дате\n3. По стоимости\n4. По статусу\n5. По количеству товаров"
#define USER_SORT_MENU "Выберите параметр по которому нужно произвести сортировку\n(при одном нажатии сортировка по возрастанию\nпри двойном нажатии сортировка по убыванию):\n1. По ID\n2. По номеру телефона\n3. По почтовому адресу\n4. По балансу\n5. По балансу бонусов\n"
#define BONUS_CARD_SORT_MENU "Выберите параметр по которому нужно произвести сортировку\n(при одном нажатии сортировка по возрастанию\nпри двойном нажатии сортировка по убыванию):\n1. По ID\n2. По количеству бонусов\n3. По проценту\n"

#define USER_MANIPULATION_ORDER_MENU "1. Добавить заказ\n2. Отменить заказ\n3. Просмотр заказов\n0. Выйти\n"

#define GOOD_CHANGE_MENU "Выберите что хотите изменить?\n1. Стоимость товара\n2. Описание товара\n3. Название товара\n4. Категорию\n5. Сохранить изменения\n0. Выйти\n"
#define ADMIN_PANEL_MENU "1. Просмотр пользователей\n2. Манипуляции с блокировками\n3. Просмотр всей информации о пользователе\n4. Поиск пользователя\n5. Манипуляции с категориями\n6. Манипуляции с товарами\n7. Манипуляции со сделками\n8. Манипуляции с бонусными картами\n0. Выйти\n"
#define MANIPULATION_BLOCKS_MENU "1. Добавить блокировку\n2. Снять блокировку\n3. Показать все блокировки\n0. Выйти\n"
#define MANIPULATION_ORDERS_MENU "1. Изменить статус сделки\n2. Просмотр всех сделок\n0. Выйти\n"
#define MANIPULATION_BONUS_CARD_MENU "1. Поиск бонусной карты\n2. Просмотр всех бонусных карт\n3. Просмотр начисления всех бонусов\n4. Просмотр начисления бонусов для определенной карты\n5. Изменить процент начисления бонусов\n0. Выйти\n"


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
	int status;// 1 - на рассмотрении, 2 - выполнен, 3 - отменен, 4 - не одобрен 
	int goodIDs[99];
	int numGoods;
};
