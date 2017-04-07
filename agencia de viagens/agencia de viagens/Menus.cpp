#include "Menus.h"


void mainMenu(TravelAgency &travelAgency)
{
	unsigned short option;
	bool exit_program = false;
	while (!exit_program)
	{
		cout << BIG_TAB << "Menu Principal" << endl << endl;
		cout << TAB << "1 - Viajar para um destino" << endl;
		cout << TAB << "2 - Viajar para vários destinos" << endl;
		cout << TAB << "3 - Visualizar Grafo." << endl;
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
			callTripToOneCity(travelAgency);
			break;
		case 2:
			clrscr();

			break;
		case 3: 
			graphviewer(travelAgency);
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

void callTripToOneCity(TravelAgency &travelAgency) {
	try{ 
		travelAgency.TripToOneCity(); 
	}
	catch (exception_or_error x) {
		cerr << endl << x.get_reason() << endl << endl;
		system("PAUSE");
		clrscr();
	}
	return;
}