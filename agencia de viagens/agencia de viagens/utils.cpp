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


void read_line(ifstream & f, string & line, uint &linenum)
{
		getline(f, line);
		++linenum;
}

Date read_date(string dateStr) {
	string tmp;
	size_t pos;
	pos = dateStr.find('/');

	if (pos == -1)
		throw exception_or_error("Data nao tem o formato DD/MM/YY");

	tmp = dateStr.substr(0, pos);
	int day = stoi(tmp);
	dateStr.erase(0, pos + 1);
	int month = stoi(dateStr);


	Date date(day,month);
	return date;
}

Node read_node(ifstream &f, uint &linenum) {
	string name, linetmp;
	float price, longitude, latitude;

	read_line(f, linetmp, linenum);

	int nodeID = stoi(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);

	name = linetmp.substr(0, linetmp.find(';'));
	linetmp.erase(0, linetmp.find(';') + 1);

	price = stof(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);
	//to add future changes for accomodation, provavelmente vai precisar de uma função propria


	longitude = stof(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);

	latitude = stof(linetmp.substr(0, linetmp.find(';')));
	linetmp.erase(0, linetmp.find(';') + 1);

	Accommodation tmp = Accommodation(price);

	while (linetmp.find(';') != -1) {
		string date1,date2;
		double percentage;
		date1 = linetmp.substr(0, linetmp.find(';'));
		linetmp.erase(0, linetmp.find(';') + 1);

		date2= linetmp.substr(0, linetmp.find(';'));
		linetmp.erase(0, linetmp.find(';') + 1);

		percentage = stod(linetmp.substr(0, linetmp.find(';')));
		linetmp.erase(0, linetmp.find(';') + 1);

		tmp.addDates(pair<Date, Date>(read_date(date1), read_date(date2)));
		tmp.addPercentage(percentage);
	}

	return Node(nodeID, name, tmp, longitude, latitude);
}

Weight read_edge(ifstream &f, uint &linenum, int &source,int &dest, int &edgeID, vector<string> &transportTypes) {
	string type, linetmp;
	float price;
	int minutes;
	Weight edgeWeight = Weight();

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

		if (std::find(transportTypes.begin(), transportTypes.end(), type) == transportTypes.end())
			transportTypes.push_back(type);

		price = stof(linetmp.substr(0, linetmp.find(';')));
		linetmp.erase(0, linetmp.find(';') + 1);

		minutes = stoi(linetmp.substr(0, linetmp.find(';')));
		linetmp.erase(0, linetmp.find(';') + 1);

		edgeWeight.addTripInfo(TripInfo(type, minutes, price));
	}

	return edgeWeight;
}

double minutesToHours(const int &time_in_minutes)
{
	return (double)time_in_minutes / 60.0;
}

double minutesToDays(const int &time_in_minutes) 
{
	return (double)time_in_minutes / (1440.0);
}

void addDaysToDate(string & dateStr, unsigned int days)
{
	if (days == 0) return;
	int day, month, year;
	stringstream ss(dateStr);
	ss >> day;
	ss.ignore();
	ss >> month;
	ss.ignore();
	ss >> year;
	while (days != 0) {
		days--;
		if (day < maxmonthday(month))
			day++;
		else if (month < 12) {
			month++;
			day = 1;
		}
		else { 
			year++; 
			month=1;
			day = 1;
		}
	}
	dateStr.clear();
	dateStr = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}


pair<int, int> CoodinatesToMap(const float longitude, const float latitude) {
	pair<int, int> coordInWindow;

	coordInWindow.first = (int)((MAP_WIDTH / 360.0) * (180 + longitude));

	coordInWindow.second = (int)((MAP_HEIGHT / 180.0) * (90 - latitude));

	return coordInWindow;
}