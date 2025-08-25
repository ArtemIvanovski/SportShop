#include "Windows.h"

int main() {
	rusActivate();
	unblockUsers();
	int id;
	while (1)
	{
		system("cls");
		switch (menu(AUTHORIZATION_MENU, 2))
		{
		case 1:
			id = showLogIn();
			if (id % 10 == 0)
				showUserPanel(id / 10);
			if (id % 10 == 1)
				showAdminPanel(id / 10);
			break;
		case 2:
			showSignUp();
			break;
		case 0:
			system("cls");
			return 0;
		}
	}
	return 0;
}
