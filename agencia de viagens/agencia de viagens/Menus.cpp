#include "Menus.h"


void mainMenu()
{
	TravelAgency tv;
	try {
		tv = TravelAgency();
		string a = "";
	}
	catch (exception_or_error x) {
		cerr << x.get_reason() << ". Tente novamente.\n";
		system("PAUSE");
		clrscr();
		return;
	}
	
}
