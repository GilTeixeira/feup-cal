#include "exceptions.h"
#include "utils.h"
#include "Menus.h"
#include <iostream>
#include <iomanip>
#include <string>

int main(){
	bool stop_program = false;
	while (!stop_program) {

		try {
			stop_program = menuTextFile();
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");
			clrscr();
		}
	}
	return 0;
}