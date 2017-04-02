#include "exceptions.h"
#include "utils.h"
#include "Menus.h"
#include <iostream>
#include <iomanip>
#include <string>

int main() {

	try {
		mainMenu();
	}
	catch (exception_or_error x) {
		cerr << x.get_reason() << ". Tente novamente.\n";
		system("PAUSE");
		clrscr();
	}
	return 0;
}