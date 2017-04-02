#include "Menus.h"


void mainMenu(TravelAgency &travelAgency)
{
	unsigned short option;
	bool exit_program = false;
	while (!exit_program)
	{
		cout << BIG_TAB << "Menu Principal" << endl << endl;
		cout << TAB << "1 - " << endl;
		cout << TAB << "2 - " << endl;
		cout << TAB << "3 - " << endl;
		cout << TAB << "4 - " << endl;
		cout << TAB << "5 - " << endl;
		cout << TAB << "0 - Sair" << endl << endl; 

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		switch (option) {
		case 1:
			clrscr();
	
			break;
		case 2:
			clrscr();

			break;
		case 3:
			clrscr();

			break;
		case 4:
			clrscr();

			break;
		case 5:
			clrscr();
			
			break;
		case 0:
			exit_program = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
	return;
}
