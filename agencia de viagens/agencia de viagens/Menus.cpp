#include "Menus.h"

bool menuTextFile()
{
	string filename; //without .txt
		try {
			cout << "\nPara voltar atras insira \"exit\"\n"
				<< "Insira o nome do ficheiro a importar: ";
			cin >> filename;
			if (filename == "exit") {
				clrscr();
				return false;
			}
			clrscr();
			//TODO chama main menu a completar
			return true;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");
			clrscr();
		}
	return false;
}


void mainMenu()
{
}
