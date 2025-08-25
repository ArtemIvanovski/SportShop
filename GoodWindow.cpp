#include "GoodWindow.h"

void showManipulationOfGood() {
	while (true)
	{
		system("cls");
		switch (menu(MANIPULATION_GOOD_MENU, 6))
		{
		case 1:
			system("cls");
			showAddGood();
			delayPress();
			break;
		case 2:
			showRemoveGood();
			break;
		case 3:
			showFindGood();
			break;
		case 4:
			system("cls");
			showAndSortGood();
			break;
		case 5:
			showChangeGood();
			break;
		case 6:
			showOfCategoryGood();
			break;
		case 0:
			return;
		}
	}
}

void showAddGood() {
	system("cls");
	char* name = NULL;

	cout << "Введите название товара: ";
	name = getInput(false);
	if (name == NULL)
		return;

	char* description = NULL;

	cout << "Введите описание товара: ";
	description = getInput(false);
	if (description == NULL)
		return;


	double price = -2;

	while (price == -2)
	{
		cout << "Введите стоимость товара: ";

		price = getInputDouble();

		if (price == -1)
			return;
	}


	int size = 0;
	int value = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));
	Category category{};

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);
		size++;
	}

	Category* categories = new Category[size];
	size = 0;

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);

		categories[size] = category;
		size++;
	}

	int selectedIdx = 0;
	char input;

	do {
		system("cls");
		cout << "Введите название товара: " << name << endl;
		cout << "Введите описание товара: " << description << endl;
		cout << "Введите стоимость товара: " << price << endl;

		cout << "Выберите категорию с помощью стрелки вниз и стрелки вверх после выбора нажмите Enter:" << endl;
		cout << "--------------------" << endl;

		for (int i = 0; i < size; i++) {
			if (i == selectedIdx) {
				cout << "> " << categories[i].name << endl;
			}
			else {
				cout << "  " << categories[i].name << endl;
			}
		}

		input = _getch();

		if (input == 27)
		{
			return;
		}

		if (input == 72 && selectedIdx > 0) {
			selectedIdx--;
		}
		else if (input == 80 && selectedIdx < size - 1) {
			selectedIdx++;
		}
	} while (input != 13);




	int id = getUniqueGoodId();

	Good good{};

	good.id = id;
	strcpy(good.description, description);
	good.value = price;
	strcpy(good.name, name);
	good.idCategory = categories[selectedIdx].id;

	writeStructToFile(FILENAME_GOODS, &good, sizeof(Good), -1);

	cout << endl << "Товар успешно добавлен!" << endl;
}

void showGood() {
	int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));

	Good good{};

	showCaptionGood();
	showBoardGood();
	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_GOODS, sizeof(Good), i, &good);
		showGood(good);
	}
	showBoardGood();
}

void showAndSortGood() {
	bool ascendingOrder = false;
	int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));
	if (value == 0)
	{
		cout << "Товаров нету!!!";
		delayPress();
		return;
	}
	int option = 0;
	while (true)
	{
		system("cls");
		showGood();
		cout << endl;
		ascendingOrder = !ascendingOrder;
		option = menu(GOOD_SORT_MENU, 5);

		if (option == 0)
			return;

		selectionSort(FILENAME_GOODS, option, sizeof(Good), 1, ascendingOrder);
	}
}

void showRemoveGood() {
	int chooceId = -2;
	int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));
	if (value == 0)
	{
		cout << "Товаров нету!!!";
		delayPress();
		return;
	}
	Good good{};
	bool found = false;

	while (true)
	{
		chooceId = -2;
		found = false;
		system("cls");
		showGood();

		while (chooceId == -2)
		{
			cout << endl << "Введите id товара, который хотите удалить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_GOODS, sizeof(Good), i, &good);

			if (good.id == chooceId)
			{
				removeStructFromFile(FILENAME_GOODS, sizeof(Good), i);

				cout << endl << "Товар успешно удален!" << endl;

				found = true;

				break;
			}
		}


		if (!found)
			cout << endl << "Введен не корректный id товара!" << endl;

		cout << "Для продолжения удаления нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}

void showFindGood() {
	system("cls");
	char searchStr[MAX_INPUT_SIZE] = "";
	char input;
	int flag = 1;
	int flagCaption = 1;
	int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));

	if (value == 0)
	{
		cout << "Товаров нету!!!";
		delayPress();
		return;
	}
	Good good{};
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
			readStructFromFile(FILENAME_GOODS, sizeof(Good), i, &good);

			if (strstr(toLower(good.description), toLower(searchStr)) != NULL ||
				strstr(toLower(good.name), toLower(searchStr)) != NULL ||
				strstr(toLower(intToString(good.id)), toLower(searchStr)) != NULL ||
				strstr(toLower(doubleToString(good.value)), toLower(searchStr)) != NULL || 
				strstr(toLower(getCategoryName(good.idCategory)), toLower(searchStr)) != NULL ) {

				if (flagCaption)
				{
					cout << endl;

					showCaptionGood();
					showBoardGood();
					flagCaption = 0;
				}

				showGood(good);
				showBoardGood();

				found = 1;
			}
		}

		if (!found) {
			cout << endl << "Ничего не найдено" << endl;
		}

	}
}

void showChangeGood() {
	double valueGood = -2;
	char* description = NULL;
	char* name = NULL;

	int chooceId = -2;
	int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));
	if (value == 0)
	{
		cout << "Товаров нету!!!";
		delayPress();
		return;
	}


	int size = 0;
	int valueCategory = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));
	Category category{};

	for (int i = 0; i < valueCategory; i++)
	{
		readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);
		size++;
	}

	Category* categories = new Category[size];
	size = 0;

	for (int i = 0; i < valueCategory; i++)
	{
		readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);

		categories[size] = category;
		size++;
	}

	int selectedIdx = 0;
	char input;

	Good good{};

	while (true)
	{
		chooceId = -2;
		system("cls");
		showGood();

		while (chooceId == -2)
		{
			cout << endl << "Введите id товара, который хотите изменить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_GOODS, sizeof(Good), i, &good);

			if (good.id == chooceId)
			{
				while (true)
				{
					system("cls");
					showCaptionGood();
					showBoardGood();
					showGood(good);
					showBoardGood();

					switch (menu(GOOD_CHANGE_MENU, 5))
					{
					case 1:
						valueGood = -2;
						while (valueGood == -2)
						{
							cout << "Введите новую стоимость товара: ";

							valueGood = getInputDouble();

							if (valueGood == -1)
								return;
						}
						good.value = valueGood;
						break;
					case 2:
						cout << "Введите новое описание товара: ";
						description = getInput(false);
						if (description == NULL)
							return;

						strcpy(good.description, description);
						break;
					case 3:
						cout << "Введите новое название товара: ";
						name = getInput(false);
						if (name == NULL)
							return;

						strcpy(good.name, name);
						break;
					case 4:
						do {
							system("cls");
							cout << "Выберите новую категорию с помощью стрелки вниз и стрелки вверх после выбора нажмите Enter:" << endl;
							cout << "--------------------" << endl;

							for (int i = 0; i < size; i++) {
								if (i == selectedIdx) {
									cout << "> " << categories[i].name << endl;
								}
								else {
									cout << "  " << categories[i].name << endl;
								}
							}

							input = _getch();

							if (input == 27)
							{
								return;
							}

							if (input == 72 && selectedIdx > 0) {
								selectedIdx--;
							}
							else if (input == 80 && selectedIdx < size - 1) {
								selectedIdx++;
							}
						} while (input != 13);

						good.idCategory = categories[selectedIdx].id;
						break;
					case 5:
						system("cls");
						writeStructToFile(FILENAME_GOODS, &good, sizeof(Good), i);
						cout << "\nДанные успешно изменены!" << endl;
						delayPress();
						return;
					case 0:
						return;
					}
				}
			}
		}

		cout << endl << "Введен не корректный id товара!" << endl;

		cout << "Для продолжения удаления нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}

void showOfCategoryGood() {
	bool ascendingOrder = false;
	int value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));
	if (value == 0)
	{
		cout << "Товаров нету!!!";
		delayPress();
		return;
	}

	int size = 0;
	value = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));
	Category category{};

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);
		size++;
	}

	Category* categories = new Category[size];
	size = 0;

	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);

		categories[size] = category;
		size++;
	}

	int selectedIdx = 0;
	char input;


	value = getCountStructsInFile(FILENAME_GOODS, sizeof(Good));

	Good good{};

	bool found = false;

	do {
		found = false;

		system("cls");

		cout << "Выберите категорию с помощью стрелки вниз и стрелки вверх после выбора нажмите Enter:" << endl;
		cout << "--------------------" << endl;

		for (int i = 0; i < size; i++) {
			if (i == selectedIdx) {
				cout << "> " << categories[i].name << endl;
			}
			else {
				cout << "  " << categories[i].name << endl;
			}
		}

		
		showCaptionGood();
		showBoardGood();
		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_GOODS, sizeof(Good), i, &good);

			if (good.idCategory == categories[selectedIdx].id)
			{
				showGood(good);
				found = true;
			}
		}
		showBoardGood();

		if (!found)
		{
			cout <<endl << "В данной категории нету товаров!" << endl;
		}

		input = _getch();

		if (input == 27)
		{
			return;
		}

		if (input == 72 && selectedIdx > 0) {
			selectedIdx--;
		}
		else if (input == 80 && selectedIdx < size - 1) {
			selectedIdx++;
		}


	} while (input != 13);

}
