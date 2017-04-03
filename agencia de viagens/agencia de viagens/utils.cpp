#include "utils.h"
			

void clrscr(void)
{
	COORD upperLeftCorner = { 0,0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}

//template<typename T>
//bool check_duplicates(const vector<T> &v, T arg)
//{
//	for (auto x : v) {
//		if (x->get_name() == arg->get_name() || x->get_code() == arg->get_code())
//			return true;
//	}
//	return false;
//}

void read_line(ifstream & f, string & line, uint &linenum)
{
		getline(f, line);
		++linenum;
}

Node read_node(ifstream &f, uint &linenum){
	string name, linetmp;
	float price;

	read_line(f, linetmp, linenum);

	int nodeID = stoi(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);

	name = linetmp.substr(0, linetmp.find(';'));
	linetmp.erase(0, linetmp.find(';') + 1);

	price = stof(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);
	//to add future changes for accomodation, provavelmente vai precisar de uma função propria

	Accommodation tmp = Accommodation(price);
	return Node(nodeID, name, tmp);
}

Weight read_edge(ifstream &f, uint &linenum, int &source,int &dest, int &edgeID) {
	string type, linetmp;
	float price;
	int minutes;
	Weight edgeWeight= Weight();

	read_line(f, linetmp, linenum);

	edgeID = stoi(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);

	source = stoi(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);

	dest = stoi(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);

	while (linetmp.find(';') != -1) {
		type = linetmp.substr(0, linetmp.find(';'));
		linetmp.erase(0, linetmp.find(';') + 1);

		price = stof(linetmp.substr(0, linetmp.find(';')));
		linetmp.erase(0, linetmp.find(';') + 1);

		minutes = stoi(linetmp.substr(0, linetmp.find(';')));
		linetmp.erase(0, linetmp.find(';') + 1);

		edgeWeight.addTripInfo(TripInfo(type, minutes, price));
	}

	return  edgeWeight;
}

double minutesToHours(const int &time_in_minutes)
{
	return (double)time_in_minutes / 60.0;
}

double minutesToDays(const int &time_in_minutes) 
{
	return (double)time_in_minutes / (1440.0);
}