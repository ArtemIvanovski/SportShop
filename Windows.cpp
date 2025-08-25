#include "Windows.h"

int showLogIn()
{
	int count = getCountStructsInFile(FILENAME_DATA, sizeof(Data));

	Data data{};
	int flagFoundLogin = 0;
	int flagFoundPassword = 0;
	char* login = NULL;
	char* password = NULL;
	Block block{};

	while (!flagFoundLogin)
	{
		system("cls");
		cout << "Авторизация:" << endl;
		cout << "Логин: ";
		login = getInput(false);

		if (login == NULL)
			return -1;

		for (int i = 0; i < count; i++)
		{
			readStructFromFile(FILENAME_DATA, sizeof(Data), i, &data);

			if (!strcmp(data.login, login))
			{
				flagFoundLogin = 1;
				break;
			}
		}

		if (!flagFoundLogin)
		{
			system("cls");
			cout << "Пользователя с таким логином: " << login << " не найдено! Чтобы повторить ввод нажмите Enter";
			if (!delayPress())
				return -1;
		}

		while (!flagFoundPassword && flagFoundLogin)
		{
			system("cls");
			cout << "Авторизация:" << endl;
			cout << "Логин: " << login << endl;
			cout << "Пароль: ";
			password = getInput(true);

			if (password == NULL)
				return -1;


			encrypt(password, data.id);

			if (!strcmp(data.password, password))
			{

				block = isBlockUser(data.id);

				if (block.id == -1)
				{
					return data.id * 10 + data.role;
				}
				else
				{
					system("cls");
					cout << "Ваш аккаунт заблокирован!" << endl;
					cout << "Причина блокировки: " << block.reason << endl;
					cout << "Дата разблокировки аккаунта: " << block.dateLockWasLifted << endl;
					delayPress();
					return -1;
				}
			}
			else
				cout << "Неверный пароль! Чтобы повторить ввод нажмите Enter";

			if (!delayPress())
				return -1;
		}
	}
}

void showSignUp()
{
	char* phoneNumber = NULL;
	char* login = NULL;
	char* password = NULL;
	char* email = NULL;


	while (1)
	{
		system("cls");
		cout << "Введите номер телефона: ";
		phoneNumber = getInput(0);

		if (phoneNumber == NULL)
			return;

		if (isValidPhoneNumber(phoneNumber))
			break;
	}

	while (1)
	{
		system("cls");
		cout << "Введите номер телефона: " << phoneNumber << endl;

		cout << "Введите ваш почтовый адрес: ";

		email = getInput(0);

		if (email == NULL)
			return;

		if (isValidEmail(email))
			break;
	}

	cout << "Придумайте логин: ";
	login = getInput(0);
	if (login == NULL)
		return;

	while (true)
	{
		cout << "Придумайте пароль: ";
		password = getInput(1);
		if (password == NULL)
			return;

		if (isValidPassword(password))
			break;
	}

	int id = getUniqueUserId();

	Data data{};

	data.id = id;

	strcpy(data.login, login);
	encrypt(password, id);
	strcpy(data.password, password);
	data.role = 0;

	writeStructToFile(FILENAME_DATA, &data, sizeof(Data), -1);

	User user{};
	user.id = id;
	user.balance = 0;
	strcpy(user.email, email);
	strcpy(user.phoneNumber, phoneNumber);

	writeStructToFile(FILENAME_USERS, &user, sizeof(User), -1);

	BonusCard bonusCard{};

	bonusCard.id = id;
	bonusCard.percent = 10;
	bonusCard.value = 0;

	writeStructToFile(FILENAME_BONUS_CARDS, &bonusCard, sizeof(BonusCard), -1);

	cout << "Регистрация успешно завершена!";

	delayPress();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showUserPanel(int id)
{
	int positionUser = 0, positionData = 0, positionBonusCard = 0;;
	User user = getUser(id, &positionUser);
	BonusCard bonusCard = getBonusCard(id, &positionBonusCard);
	Data data = getData(id, &positionData);

	while (1)
	{
		system("cls");

		showProfile(user, data, bonusCard, true);

		switch (menu(USER_PANEL_MENU, 7))
		{
		case 1:
			system("cls");
			showAndSortGood();
			break;
		case 2:
			system("cls");
			showOfCategoryGood();
			break;
		case 3:
			system("cls");
			showFindGood();
			break;
		case 4:
			showInputBalance(&user, positionUser);
			break;
		case 5:
			showChangeProfile(&user, &data, bonusCard, positionUser, positionData);
			user = getUser(id, &positionUser);
			data = getData(id, &positionData);
			break;
		case 6:
			showManipulationOfOrdersUser(id);
			break;
		case 7:
			system("cls");
			showBonusOrderHistory(id);
			delayPress();
			break;
		case 0:
			system("cls");
			return;
		}
	}
}

void showProfile(User user, Data data, BonusCard bonuscard, bool isUser) {
	cout << "------------ Профиль -------------" << endl;
	cout << "ID: " << user.id << endl;
	cout << "Логин: " << data.login << endl;
	cout << "Номер телефона: " << user.phoneNumber << endl;
	cout << "Почтовый адрес: " << user.email << endl;
	if (isUser) {
		cout << "Баланс: " << user.balance << endl;
		cout << "Бонусные баллы: " << bonuscard.value << endl;
		cout << "Бонусный процент: " << bonuscard.percent << endl;
	}
	cout << "----------------------------------" << endl;
}

void showChangeProfile(User* user, Data* data, BonusCard bonuscard, int positionUser, int positionData)
{
	char* login = NULL;
	char* phoneNumber = NULL;
	char* email = NULL;

	while (true)
	{
		system("cls");
		showProfile(*user, *data, bonuscard, false);
		switch (menu(CHANGE_PROFILE_MENU, 5))
		{
		case 1:
			while (true)
			{
				cout << "\nВведите новый номер телефона: ";
				phoneNumber = getInput(0);

				if (phoneNumber == NULL)
					break;

				if (isValidPhoneNumber(phoneNumber)) {
					strcpy(user->phoneNumber, phoneNumber);
					break;
				}
			}
			break;
		case 2:
			while (true)
			{
				cout << "\nВведите новый почтовый адрес: ";
				email = getInput(0);

				if (email == NULL)
					break;

				if (isValidEmail(email)) {
					strcpy(user->email, email);
					break;
				}
			}
			break;
		case 3:
			cout << "\nПридумайте новый логин: ";
			login = getInput(0);
			if (login != NULL)
				strcpy(data->login, login);
			break;
		case 4:
			showChangePassword(*data, positionData);
			break;
		case 5:
			system("cls");
			writeStructToFile(FILENAME_DATA, data, sizeof(Data), positionData);
			writeStructToFile(FILENAME_USERS, user, sizeof(User), positionUser);
			cout << "\nДанные успешно изменены!" << endl;
			delayPress();
			return;
		case 0:
			return;
		}
	}
}

void showChangePassword(Data data, int position) {
	char* password = NULL;

	while (1)
	{
		system("cls");
		cout << "Введите старый пароль: ";
		password = getInput(1);
		if (password == NULL)
			return;

		encrypt(password, data.id);
		if (!strcmp(data.password, password))
			break;
	}

	cout << "Придумайте новый пароль: ";
	password = getInput(1);
	if (password == NULL)
		return;

	encrypt(password, data.id);

	writeStructToFile(FILENAME_DATA, &data, sizeof(Data), position);

	system("cls");

	cout << "\nПароль успешно изменен!" << endl;
	delayPress();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showInputBalance(User* user, int positionUser) {

	double value;

	do
	{
		value = -2;
		system("cls");

		cout << "Введите сумму которую хотите внести: ";

		value = getInputDouble();

		if (value == -1)
		{
			return;
		}

	} while (value == -2);

	user->balance += value;

	writeStructToFile(FILENAME_USERS, user, sizeof(User), positionUser);
	cout << "Сумма успешно внесена!" << endl;
	delayPress();
}

void showManipulationOfOrdersUser(int id) {
	while (true)
	{
		system("cls");
		switch (menu(USER_MANIPULATION_ORDER_MENU, 3))
		{
		case 1:
			system("cls");
			showAddOrder(id);
			break;
		case 2:
			system("cls");
			showCancelOrder(id);
			break;
		case 3:
			showAndSortOrders(id);
			break;
		case 0:
			return;
		}
	}
}

void showOrders(int id) {
	int value = getCountStructsInFile(FILENAME_ORDERS, sizeof(Order));

	Order order{};

	
	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);

		if (order.idUser == id || id == -1) {
			showOrder(order);
		}
	}
}

void showAndSortOrders(int id) {
	bool ascendingOrder = false;
	int value = getCountStructsInFile(FILENAME_ORDERS, sizeof(Order));

	bool flag = true;

	Order order{};

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);

		if (order.idUser == id || id == -1)
			flag = false;

	}

	if (flag)
	{
		cout << "Сделок нету!!!";
		delayPress();
		return;
	}


	int option = 0;
	while (true)
	{
		system("cls");
		showOrders(id);
		cout << endl;
		ascendingOrder = !ascendingOrder;
		option = menu(ORDER_SORT_MENU, 5);

		if (option == 0)
			return;

		selectionSort(FILENAME_ORDERS, option, sizeof(Order), 2, ascendingOrder);
	}
}

void showCancelOrder(int id) {
	int value = getCountStructsInFile(FILENAME_ORDERS, sizeof(Order));

	bool flag = true;

	Order order{};

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);

		if (order.idUser == id)
			flag = false;

	}

	if (flag)
	{
		cout << "Сделок нету!!!";
		delayPress();
		return;
	}

	int chooceId = -2;

	flag = false;

	while (true)
	{
		chooceId = -2;
		system("cls");
		showOrders(id);

		while (chooceId == -2)
		{
			cout << endl << "Введите id сделки, которую хотите отменить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);

			if (order.id == id) {
				order.status = 3;
				system("cls");
				writeStructToFile(FILENAME_ORDERS, &order, sizeof(Order), i);
				cout << "\nСделка успешно отменена!" << endl;
				delayPress();
				return;
			}
		}


		cout << endl << "Введен не корректный id сделки!" << endl;

		cout << "Для продолжения отмены нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}

}

void showAddOrder(int id) {
	int idGoods[99]{};
	int numGood = 0;
	int positionUser = 0;
	User user = getUser(id, &positionUser);
	int chooceId = -2;
	double value = 0.0;
	int position = 0;

	BonusCard bonusCard = getBonusCard(user.id, &position);
	Order order{};
	Good good{};

	int bonusValue = -2;
	int valueGood = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));

	while (true)
	{
		system("cls");
		chooceId = -2;

		showGood();
		cout << endl;

		cout << "Ваш баланс: " << user.balance << endl;
		cout << "Количество бонусов: " << bonusCard.value << endl;
		cout << "Сумма корзины: " << value << endl;
		cout << "Количество товаров в корзине: " << numGood << endl;
		cout << "ID товаров в корзине: ";

		for (int i = 0; i < numGood; i++)
		{
			cout << idGoods[i] << " ";
		}

		cout << endl;

		while (chooceId == -2)
		{
			cout << endl << "Введите id товара, который хотите добавить в корзину, для продолжения нажмите Tab: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;

			if (chooceId == -99) {

				if (value > user.balance + bonusCard.value)
				{
					system("cls");
					cout << "Недостаточный баланс!" << endl;
					delayPress();
					return;
				}
				do
				{
					cout << endl << "Введите количество бонусов, которые вы хотите потратить: ";
					bonusValue = getInputInt();

					if (bonusValue == -1)
						return;

				} while (bonusValue == -2 || bonusValue > bonusCard.value || bonusValue > value);

				strcpy(order.date, getCurrentDate());
				order.id = getUniqueOrderId();
				order.status = 1;
				order.idUser = id;
				order.value = value;
				order.numGoods = numGood;

				for (int i = 0; i < numGood; i++)
				{
					order.goodIDs[i] = idGoods[i];
				}

				
				user.balance -= value;

				if (bonusValue != 0)
				{
					bonusCard.value -= bonusValue;
					user.balance += bonusValue;

					BonusOrder bonusOrder{};
					bonusOrder.id = getUniqueBonusOrderId();
					bonusOrder.idOrder = order.id;
					strcpy(bonusOrder.date, getCurrentDate());
					bonusOrder.value = -1 * bonusValue;
					bonusOrder.idBonusCard = bonusCard.id;

					writeStructToFile(FILENAME_BONUS_ORDERS, &bonusOrder, sizeof(BonusOrder), -1);
					writeStructToFile(FILENAME_BONUS_CARDS, &bonusCard, sizeof(BonusCard), position);
				}

				writeStructToFile(FILENAME_USERS, &user, sizeof(User), positionUser);
				writeStructToFile(FILENAME_ORDERS, &order, sizeof(Order), -1);
				system("cls");

				cout << "Сделка успешно добавлена!" << endl;
				delayPress();
				return;
			}
		}

		for (int i = 0; i < valueGood; i++)
		{
			readStructFromFile(FILENAME_GOODS, sizeof(Good),i,&good);
			if (good.id == chooceId)
			{
				value += good.value;
				idGoods[numGood] = chooceId;
				numGood++;
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////


void showBonusOrderHistory(int id) {
	int value = getCountStructsInFile(FILENAME_BONUS_ORDERS, sizeof(BonusOrder));

	BonusOrder bonusOrder{};

	showCaptionBonusOrder(id);
	showBoardBonusOrder(id);

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_BONUS_ORDERS, sizeof(BonusOrder), i, &bonusOrder);

		if (bonusOrder.idBonusCard == id || id == -1) {
			showBonusOrder(bonusOrder, id);
		}
	}

	showBoardBonusOrder(id);
}


void showAdminPanel(int id) {
	BonusCard bonusCard{};
	int positionUser = 0, positionData = 0;
	User user = getUser(id, &positionUser);
	Data data = getData(id, &positionData);

	while (1)
	{
		system("cls");

		showProfile(user, data, bonusCard, false);

		switch (menu(ADMIN_PANEL_MENU, 8))
		{
		case 1:
			system("cls");
			showAndSortUsers(id);
			break;
		case 2:
			system("cls");
			showManipulationOfBlocks(id);
			break;
		case 3:
			system("cls");
			showAllInformationUser(id);
			break;
		case 4:
			system("cls");
			showFindUser(id);
			break;
		case 5:
			system("cls");
			showManipulationOfCategory();
			break;
		case 6:
			system("cls");
			showManipulationOfGood();
			break;
		case 7:
			system("cls");
			showManipulationOfOrder();
			break;
		case 8:
			system("cls");
			showManipulationOfBonusCard();
			break;
		case 0:
			system("cls");
			return;
		}
	}
}

///////////////////////BONUS CARD//////////////////////////
void showManipulationOfBonusCard() {
	while (true)
	{
		system("cls");
		switch (menu(MANIPULATION_BONUS_CARD_MENU, 5))
		{
		case 1:
			showFindBonusCard();
			break;
		case 2:
			showAndSortBonusCard();
			break;
		case 3:
			system("cls");
			showBonusOrderHistory(-1);
			delayPress();
			break;
		case 4:
			system("cls");
			showBonusCardInformation();
			break;
		case 5:
			system("cls");
			showChangePercentBonusCard();
			break;
		case 0:
			return;
		}
	}
}

void showBonusCards() {
	int value = getCountStructsInFile(FILENAME_BONUS_CARDS, sizeof(BonusCard));

	BonusCard bonusCard{};

	showCaptionBonusCard();
	showBoardBonusCard();
	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_BONUS_CARDS, sizeof(BonusCard), i, &bonusCard);
		showBonusCard(bonusCard);
	}
	showBoardBonusCard();
}

void showAndSortBonusCard() {
	bool ascendingOrder = false;

	int value = getCountStructsInFile(FILENAME_BONUS_CARDS, sizeof(BonusCard));
	if (value == 0)
	{
		cout << "Бонусных карт нету!!!";
		delayPress();
		return;
	}

	int option = 0;

	while (true)
	{
		system("cls");
		showBonusCards();
		cout << endl;
		ascendingOrder = !ascendingOrder;
		option = menu(BONUS_CARD_SORT_MENU, 3);

		if (option == 0)
			return;

		selectionSort(FILENAME_BONUS_CARDS, option, sizeof(BonusCard), 4, ascendingOrder);
	}
}

void showFindBonusCard() {
	system("cls");
	char searchStr[MAX_INPUT_SIZE] = "";
	char input;
	int flag = 1;
	int flagCaption = 1;
	int value = getCountStructsInFile(MANIPULATION_BONUS_CARD_MENU, sizeof(BonusCard));

	if (value == 0)
	{
		cout << "Бонусных карт нету!!!";
		delayPress();
		return;
	}
	BonusCard bonusCard{};
	while (1) {
		if (flag)
		{
			cout << "Поиск: " << searchStr;
			flag = 0;
		}
		input = _getch();
		system("cls");
		if (input == 27) {
			return;
		}
		else if (input == 8 && strlen(searchStr) > 0) {
			searchStr[strlen(searchStr) - 1] = '\0';
		}
		else {
			strncat(searchStr, &input, 1);
		}
		cout << "Поиск: " << searchStr;


		int found = 0;
		flagCaption = 1;
		for (int i = 0; i < value; ++i) {
			readStructFromFile(MANIPULATION_BONUS_CARD_MENU, sizeof(BonusCard), i, &bonusCard);

			if (strstr(toLower(intToString(bonusCard.id)), toLower(searchStr)) != NULL ||
				strstr(toLower(intToString(bonusCard.value)), toLower(searchStr)) != NULL ||
				strstr(toLower(doubleToString(bonusCard.percent)), toLower(searchStr)) != NULL) {

				if (flagCaption)
				{
					cout << endl;

					showCaptionBonusCard();
					showBoardBonusCard();
					flagCaption = 0;
				}

				showBonusCard(bonusCard);
				showBoardBonusCard();

				found = 1;
			}
		}

		if (!found) {
			cout << endl << "Ничего не найдено" << endl;
		}

	}
}

void showBonusCardInformation() {
	int chooceId = -2;
	int value = getCountStructsInFile(FILENAME_BONUS_CARDS, sizeof(BonusCard));
	if (value == 0)
	{
		cout << "Бонусных карт нету!!!";
		delayPress();
		return;
	}

	BonusCard bonusCard{};
	bool found = false;

	while (true)
	{
		chooceId = -2;
		found = false;
		system("cls");
		showBonusCards();

		while (chooceId == -2)
		{
			cout << endl << "Введите id бонусной карты, историю которой хотите просмотреть: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_BONUS_CARDS, sizeof(Block), i, &bonusCard);

			if (bonusCard.id == chooceId)
			{
				cout << endl << endl;

				showBonusOrderHistory(bonusCard.id);

				found = true;

				break;
			}
		}


		if (!found)
			cout << endl << "Введен не корректный id бонусной карты!" << endl;

		cout << "Для продолжения нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}

void showChangePercentBonusCard() {
	int chooceId = -2;
	int value = getCountStructsInFile(FILENAME_BONUS_CARDS, sizeof(BonusCard));
	if (value == 0)
	{
		cout << "Бонусных карт нету!!!";
		delayPress();
		return;
	}

	BonusCard bonusCard{};
	bool found = false;
	double percent = -2;

	while (true)
	{
		chooceId = -2;
		percent = -2;
		found = false;
		system("cls");
		showBonusCards();

		while (chooceId == -2)
		{
			cout << endl << "Введите id бонусной карты, процент которой хотите изменить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_BONUS_CARDS, sizeof(Block), i, &bonusCard);

			if (bonusCard.id == chooceId)
			{
				cout << endl << endl;

				do
				{
					cout << "Введите новый процент начисления бонусов";

					percent = getInputDouble();

					if (percent == -1)
						return;

				} while (percent == -2);

				bonusCard.percent = percent;

				writeStructToFile(FILENAME_BONUS_CARDS, &bonusCard, sizeof(BonusCard), i);

				found = true;

				break;
			}
		}


		if (!found)
			cout << endl << "Введен не корректный id бонусной карты!" << endl;

		cout << "Для продолжения нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}


//////////////////////////////////////////////////












void showManipulationOfOrder() {
	while (true)
	{
		system("cls");
		switch (menu(MANIPULATION_ORDERS_MENU, 2))
		{
		case 1:
			showChangeStatusOrder();
			break;
		case 2:
			showAndSortOrders(-1);
			break;
		case 0:
			return;
		}
	}
}

void showChangeStatusOrder() {
	int value = getCountStructsInFile(FILENAME_ORDERS, sizeof(Order));

	bool flag = true;

	Order order{};

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);

		if (order.status == 1) {
			flag = false;
			break;
		}
	}

	if (flag)
	{
		cout << "Сделок на рассмотрении нету!!!";
		delayPress();
		return;
	}

	value = getCountStructsInFile(FILENAME_ORDERS, sizeof(Order));

	
	int chooceId = -2;
	char input = 0;
	while (true)
	{
		chooceId = -2;
		system("cls");

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);

			if (order.status == 1) {
				showOrder(order);
				cout << endl;
			}
		}

		while (chooceId == -2)
		{
			cout << endl << "Введите id сделки, статус которой хотите изменить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_ORDERS, sizeof(Order), i, &order);

			if (order.id == chooceId) {
				system("cls");

				showOrder(order);

				cout << endl << "Для смены статуса на 'выполнен' нажмите Enter,\nдля смены статуса на 'не одобрен' нажмите Tab:  ";
				do
				{
					input = _getch();

					if (input == 27 || input == 13 || input == 9)
						break;

				} while (true);

				if (input == 27)
					return;

				if (input == 13)
				{
					order.status = 2;

					int position = 0;
					BonusCard bonusCard = getBonusCard(order.idUser, &position);

					BonusOrder bonusOrder{};
					bonusOrder.id = getUniqueBonusOrderId();
					bonusOrder.idOrder = order.id;
					strcpy(bonusOrder.date, getCurrentDate());
					bonusOrder.value = (int)(order.value * bonusCard.percent / 100);
					bonusOrder.idBonusCard = bonusCard.id;

					bonusCard.value += (int)(order.value * bonusCard.percent / 100);

					writeStructToFile(FILENAME_BONUS_ORDERS, &bonusOrder, sizeof(BonusOrder), -1);
					writeStructToFile(FILENAME_BONUS_CARDS, &bonusCard, sizeof(BonusCard), position);
				}
				else
				{
					order.status = 4;
				}

				system("cls");
				writeStructToFile(FILENAME_ORDERS, &order, sizeof(Order), i);
				cout << "\nСтатус сделки успешно изменен!" << endl;
				delayPress();
				return;
			}
		}


		cout << endl << "Введен не корректный id сделки!" << endl;

		cout << "Для продолжения отмены нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}

}


//////////////////user///////////////////////////////
void showUsers(int id) {
	int value = getCountStructsInFile(FILENAME_USERS, sizeof(User));

	User user{};

	showCaptionUser();
	showBoardUser();
	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_USERS, sizeof(User), i, &user);
		if (user.id != id)
			showUser(user);
	}
	showBoardUser();
}

void showAndSortUsers(int id) {
	bool ascendingOrder = false;

	int value = getCountStructsInFile(FILENAME_USERS, sizeof(User));
	if (value == 0)
	{
		cout << "Пользователей нету!!!";
		delayPress();
		return;
	}

	int option = 0;

	while (true)
	{
		system("cls");
		showUsers(id);
		cout << endl;
		ascendingOrder = !ascendingOrder;
		option = menu(USER_SORT_MENU, 5);

		if (option == 0)
			return;

		selectionSort(FILENAME_USERS, option, sizeof(User), 3, ascendingOrder);
	}
}

void showFindUser(int id) {
	system("cls");
	char searchStr[MAX_INPUT_SIZE] = "";
	char input;
	int flag = 1;
	int flagCaption = 1;
	int value = getCountStructsInFile(FILENAME_USERS, sizeof(User));

	if (value == 0)
	{
		cout << "Пользователей нету!!!";
		delayPress();
		return;
	}
	User user{};
	while (1) {
		if (flag)
		{
			cout << "Поиск: " << searchStr;
			flag = 0;
		}
		input = _getch();
		system("cls");
		if (input == 27) {
			return;
		}
		else if (input == 8 && strlen(searchStr) > 0) {
			searchStr[strlen(searchStr) - 1] = '\0';
		}
		else {
			strncat(searchStr, &input, 1);
		}
		cout << "Поиск: " << searchStr;


		int found = 0;
		flagCaption = 1;
		for (int i = 0; i < value; ++i) {
			readStructFromFile(FILENAME_USERS, sizeof(User), i, &user);

			if ((strstr(toLower(user.phoneNumber), toLower(searchStr)) != NULL ||
				strstr(toLower(user.email), toLower(searchStr)) != NULL ||
				strstr(toLower(intToString(user.id)), toLower(searchStr)) != NULL ||
				strstr(toLower(intToString(user.balance)), toLower(searchStr)) != NULL) && user.id != id) {

				if (flagCaption)
				{
					cout << endl;

					showCaptionUser();
					showBoardUser();
					flagCaption = 0;
				}

				showUser(user);
				showBoardUser();

				found = 1;
			}
		}

		if (!found) {
			cout << endl << "Ничего не найдено" << endl;
		}

	}
}

void showAllInformationUser(int id) {
	system("cls");
	int value = getCountStructsInFile(FILENAME_USERS, sizeof(User));

	if (value == 0)
	{
		cout << "Пользователей нету!!!";
		delayPress();
		return;
	}
	User user{};
	int chooceId = -2;
	bool found;
	int positionCard;
	while (true)
	{
		chooceId = -2;
		found = false;
		system("cls");
		showUsers(id);

		while (chooceId == -2)
		{
			cout << endl << "Введите id пользователя, полную информацию о котором хотите узнать: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_USERS, sizeof(User), i, &user);

			if (user.id == chooceId)
			{
				system("cls");
				cout << "Информация о пользователе:" << endl;
				showCaptionUser();
				showBoardUser();
				showUser(user);
				showBoardUser();

				cout << "Информация о бонусной карте:" << endl;
				BonusCard bonusCard = getBonusCard(user.id, &positionCard);
				showCaptionBonusCard();
				showBoardBonusCard();
				showBonusCard(bonusCard);
				showBoardBonusCard();

				cout << "Информация о истории бонусной карты:" << endl;
				showBonusOrderHistory(user.id);

				cout << "Информация о транзакциях:" << endl;
				showOrders(user.id);


				found = true;
				delayPress();
				return;
			}
		}


		if (!found)
			cout << endl << "Введен не корректный id пользователя!" << endl;

		cout << "Для продолжения нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}


//////////////////////////BLOCK////////////////////////////

void showManipulationOfBlocks(int id) {
	while (true)
	{
		system("cls");
		switch (menu(MANIPULATION_BLOCKS_MENU, 3))
		{
		case 1:
			system("cls");
			showAddBlock(id);
			delayPress();
			break;
		case 2:
			showRemoveBlock();
			break;
		case 3:
			system("cls");
			showBlocks();
			delayPress();
			break;
		case 0:
			return;
		}
	}
}

void showAddBlock(int id) {
	system("cls");

	showUsers(id);

	cout << endl;

	char* reason = NULL;

	cout << "Введите причину блокировки: ";
	reason = getInput(false);
	if (reason == NULL)
		return;


	int userId = -2;

	while (userId == -2)
	{
		cout << "Введите id пользователя: ";

		userId = getInputInt();

		if (userId == id)
			userId = -2;

		if (userId == -1)
			return;
	}

	char* date;

	while (1)
	{
		cout << "Введите дату разблокировки: ";
		date = getInput(0);

		if (date == NULL)
			return;

		if (isValidDate(date))
			break;
	}

	int idBlock = getUniqueBlockId();

	Block block{};

	block.id = idBlock;
	strcpy(block.reason, reason);
	strcpy(block.dateLockWasLifted, date);
	block.idUser = userId;

	writeStructToFile(FILENAME_BLOCKS, &block, sizeof(Block), -1);

	cout << endl << "Блокировка успешно добавлена!" << endl;
}

void showBlocks() {
	int value = getCountStructsInFile(FILENAME_BLOCKS, sizeof(Block));

	Block block{};

	showCaptionBlock();
	showBoardBlock();
	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_BLOCKS, sizeof(Block), i, &block);
		showBlock(block);
	}
	showBoardBlock();
}

void showRemoveBlock() {
	int chooceId = -2;
	int value = getCountStructsInFile(FILENAME_BLOCKS, sizeof(Block));
	if (value == 0)
	{
		cout << "Блокировок нету!!!";
		delayPress();
		return;
	}
	Block block{};
	bool found = false;

	while (true)
	{
		chooceId = -2;
		found = false;
		system("cls");
		showBlocks();

		while (chooceId == -2)
		{
			cout << endl << "Введите id блокировки, который хотите удалить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_BLOCKS, sizeof(Block), i, &block);

			if (block.id == chooceId)
			{
				removeStructFromFile(FILENAME_BLOCKS, sizeof(Block), i);

				cout << endl << "Блокировка успешно удалена!" << endl;

				found = true;

				break;
			}
		}


		if (!found)
			cout << endl << "Введен не корректный id блокировки!" << endl;

		cout << "Для продолжения удаления нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}