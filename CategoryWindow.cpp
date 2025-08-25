#include "CategoryWindow.h"

void showManipulationOfCategory()
{
	while (true)
	{
		system("cls");
		switch (menu(MANIPULATION_CATEGORY_MENU, 4))
		{
		case 1:
			system("cls");
			showCategorys();
			delayPress();
			break;
		case 2:
			showChangeCategory();
			break;
		case 3:
			showRemoveCategory();
			break;
		case 4:
			showAddCategory();
			break;
		case 0:
			return;
		}
	}
}

void showRemoveCategory() {
	int chooceId = -2;
	int value = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));
	Category category{};
	bool found = false;

	while (true)
	{
		chooceId = -2;
		found = false;
		system("cls");
		showCategorys();

		while (chooceId == -2)
		{
			cout << endl << "Введите id категории, которую хотите удалить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);

			if (category.id == chooceId)
			{
				removeStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i);

				cout << endl << "Категория успешно удалена!" << endl;

				found = true;

				break;
			}
		}

		if (!found)
			cout << endl << "Введен не корректный id категории!" << endl;

		cout << "Для продолжения удаления нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}

void showChangeCategory() {
	int chooceId = -2;
	int value = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));
	Category category{};
	char* name = NULL;
	bool found = false;

	while (true)
	{
		chooceId = -2;
		found = false;
		system("cls");
		showCategorys();

		while (chooceId == -2)
		{
			cout << endl << "Введите id категории, которую хотите изменить: ";
			chooceId = getInputInt();

			if (chooceId == -1)
				return;
		}

		for (int i = 0; i < value; i++)
		{
			readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);

			if (category.id == chooceId)
			{
				cout << "Введите новое название категории: ";
				name = getInput(false);
				if (name == NULL)
					return;

				strcpy(category.name, name);

				writeStructToFile(FILENAME_CATEGORIES, &category, sizeof(Category), i);

				cout << endl << "Название категории успешно изменено!" << endl;

				found = true;

				break;
			}
		}


		if (!found)
			cout << endl << "Введен не корректный id категории!" << endl;

		cout << "Для продолжения изменения нажмите Enter, для выхода Esc" << endl;

		if (!delayPress())
			return;
	}
}

void showAddCategory()
{
	system("cls");
	char* name = NULL;

	while (true)
	{
		cout << "Введите название новой категории: ";
		name = getInput(false);
		if (name == NULL)
			return;

		if (strlen(name) > 1)
			break;
	}

	int id = getUniqueCategoryId();

	Category category{};

	category.id = id;

	strcpy(category.name, name);

	writeStructToFile(FILENAME_CATEGORIES, &category, sizeof(Category), -1);

	cout << endl << "Категория успешно добавлена!" << endl;
	delayPress();
}

void showCategorys() {
	int value = getCountStructsInFile(FILENAME_CATEGORIES, sizeof(Category));

	Category category{};

	showCaptionCategory();
	showBoardCategory();
	for (int i = 0; i < value; i++)
	{
		readStructFromFile(FILENAME_CATEGORIES, sizeof(Category), i, &category);
		showCategory(category);
	}
	showBoardCategory();
}
