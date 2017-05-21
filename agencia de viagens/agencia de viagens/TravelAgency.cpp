#include "TravelAgency.h"


TravelAgency::TravelAgency()
{
	uint linenum = 0;
	string linetmp;
	ifstream f;

	f.open("Nodes.txt");
	if (!f.is_open()) {
		throw exception_or_error("O ficheiro Nodes.txt nao foi encontrado verifique se o mesmo existe ou esta em local adequado");
	}

	read_line(f, linetmp, linenum);
	if (linetmp != "#Vertex_start") {
		throw exception_or_error("O ficheiro esta corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #Vertex_start");
	}

	while (f.peek() != '#') {
		travelAgencyGraph.addVertex(Node(read_node(f, linenum)));
	}

	read_line(f, linetmp, linenum);
	if (linetmp != "#End")
		throw exception_or_error("O ficheiro esta corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #End");

	f.close();
	linenum = 0;
	f.open("Edges.txt");
	if (!f.is_open()) {
		throw exception_or_error("O ficheiro Edges.txt nao foi encontrado verifique se o mesmo existe ou esta em local adequado");
	}

	read_line(f, linetmp, linenum);
	if (linetmp != "#Edges_start") {
		throw exception_or_error("O ficheiro esta corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #Edges_start");
	}

	while (f.peek() != '#') {
		int sourceID, destID, edgeID;
		Weight tmpW = read_edge(f, linenum, sourceID, destID, edgeID,transportTypes);
		Node source = Node(sourceID);
		Node dest = Node(destID);
		travelAgencyGraph.addEdge(source, dest, tmpW, edgeID);
	}

	read_line(f, linetmp, linenum);
	if (linetmp != "#End")
		throw exception_or_error("O ficheiro esta corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #End");

	f.close();
	return;
}


void TravelAgency::TripToOneCity()
{
	unsigned int idSource, idDest, accommodationTime;
	string dateStr;
	set <string> notWantedTypes;
	
	vector <Vertex *> allCitys = travelAgencyGraph.getVertexes();
	if (allCitys.size() == 0) throw exception_or_error("O grafo nao contem nenhuma informação verifique o ficheiro de texto.");

	cout << BIG_TAB << "Assitente de Viagem" << endl << endl;

	Vertex* source = read_current_city(idSource);
	if (source == nullptr)
		return;
	
	cout << "Insira o numero correpondente a cidade que pretende visitar, 0 para cancelar: " << endl;
	cin >> idDest;

	if (!cin.good() || idDest > (uint)allCitys.at(allCitys.size() - 1)->getInfo().getNodeID()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido! Tente novamente.");
	}

	if (idDest == 0) return;
	if (idSource == idDest) throw  exception_or_error("Escolheu a mesma cidade para a origem e o seu destino!");


	Vertex* dest = travelAgencyGraph.getVertex(Node(idDest));

	cout << "Insira a data em que pretende iniciar a viagem: " << endl;
	cin >> dateStr;
	Date date = Date(dateStr);

	cout << "Deseja adquirir alojamento por quanto tempo (0 se não pretender): " << endl;
	cin >> accommodationTime;

	if (!cin.good()||accommodationTime>60) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido! Tente novamente.");
	}
	
	notWantedTypes= load_notWantedTypes();

	list <Vertex> shortestPath;
	if (travelAgencyGraph.shortestPath((*source), (*dest), shortestPath, notWantedTypes) == 0.0) {
		throw exception_or_error("O destino que escolheu e impossivel de alcançar apartir da origem dada");
	}
	clrscr();
	cout << "A sua viagem foi calculada, aqui esta a sua informacao: " << endl << endl;
	outPut_TripToOneCity(shortestPath, accommodationTime, dateStr, notWantedTypes);
	system("Pause");
	clrscr();
	return;
}



set<string> TravelAgency::load_notWantedTypes()
{
	int i = 1;
	set<string> notWantedTypes;
	for (string type : transportTypes){
		cout << TAB << i << " - " << type << endl;
		i++;
	}
	cout << TAB << 0 << " - " << "Cancelar" << endl << endl;

	while (true) {
		uint option;
		cout << "Insira o numero correpondente a um dos transportes que nao quer utilizar(0 se nao tiver preferencia ou se ja inseriu todos os que nao deseja utilizar): " << endl;
		cin >> option;

		if (!cin.good() || option> transportTypes.size()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw exception_or_error("O input nao e valido! Tente novamente.");
		}
		if (option == 0)
			return notWantedTypes;
		notWantedTypes.insert(transportTypes.at(option - 1));
	}
}


void TravelAgency::outPut_TripToOneCity(const list<Vertex> &shortestPath, uint accommodationTime, string dateStr, const set<string> &notWantedTypes)
{

	list<Vertex>::const_iterator it_i = shortestPath.end();
	list<Vertex>::const_iterator it_f = shortestPath.begin();
	it_i--;

	
	cout << "Tranportes a usar: " << endl << endl;
	while (it_i != it_f) {
		cout << "De: " << it_i->getInfo().getCityName() << endl;
		vector<Edge> tmp= it_i->getEdges();
		it_i--;
		cout << "Para: " << it_i->getInfo().getCityName() << endl;
		TripInfo tmpTrip("",0,0);

		for (Edge edge : tmp) {
			if (edge.getDest()->getInfo() == it_i->getInfo()) {
				tmpTrip=edge.getWeight().getEdgeWeightPrice(notWantedTypes);
				break;
			}
		}

		cout << tmpTrip << endl;
	}

	cout << endl;
	if (accommodationTime == 0) {
		return;
	}

	cout << "Preco de alojamento para " << accommodationTime << " dias apartir do dia " 
		<< dateStr << ": ";
	cout <<  std::fixed << std::setprecision(2) 
		<< accommodationTime*it_f->getInfo().getAccommodation().getPrice(dateStr) << endl << endl;

	return;
}

void TravelAgency::CustomTrip()
{

	unsigned int  idSource,idDest, accommodationTime;
	vector<Vertex> visited;
	vector<Vertex> toVisit;
	map<string,uint> accomTime;

	set <string> notWantedTypes;
	string dateStr;
	
	cout << BIG_TAB << "Assitente de Viagem" << endl << endl;

	Vertex* source = read_current_city(idSource);

	if (source == nullptr)
		return;

	visited.push_back((*source));

	vector <Vertex *> allCitys = travelAgencyGraph.getVertexes();
	while (true) {
		cout << "Insira o numero correpondente a uma das cidades que pretende visitar, 0 se ja inseriu todas as pretendidadas: " << endl;
		cin >> idDest;

		if (!cin.good() || idDest > (uint)allCitys.at(allCitys.size() - 1)->getInfo().getNodeID()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw exception_or_error("O input nao e valido! Tente novamente.");
		}

		if (idDest == 0) break;
		if (idSource == idDest) throw exception_or_error("Escolheu a mesma cidade para a origem e para um dos seus destinos!");
		
		for (Vertex checkingDup: toVisit) {
			if (checkingDup.getInfo().getNodeID() == idDest) 
				throw exception_or_error("Nao pode escolher o mesmo destino mais que uma vez!");
		}

		cout << "Deseja adquirir alojamento por quanto tempo nesta cidade (0 se não pretender): " << endl;
		cin >> accommodationTime;

		if (!cin.good()||accommodationTime>60) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw exception_or_error("O input nao e valido! Tente novamente.");
		}

		Vertex* dest = travelAgencyGraph.getVertex(Node(idDest));
		toVisit.push_back((*dest));
		accomTime.insert(make_pair(dest->getInfo().getCityName(), accommodationTime));
	}

	if (toVisit.size() == 0) return;

	cout << "Insira a data em que pretende iniciar a viagem: " << endl;
	cin >> dateStr;
	Date date = Date(dateStr);

	notWantedTypes = load_notWantedTypes();
	vector < list <Vertex> > shortestPath;
	travelAgencyGraph.customTripAlgorithm(visited, toVisit,shortestPath, notWantedTypes);

	clrscr();
	cout << BIG_TAB << "Calculamos a sua viagem aqui estao as informacoes: " << endl << endl << endl;
	outPut_CustomTrip(shortestPath, accomTime, dateStr, notWantedTypes);
	
	system("PAUSE");
	clrscr();
	return;
}

Vertex* TravelAgency::read_current_city(unsigned int &idSource) {
	
	vector <Vertex *> allCitys = travelAgencyGraph.getVertexes();
	if (allCitys.size() == 0) throw exception_or_error("O grafo não contém nenhuma informação verifique o ficheiro de texto.");

	for (Vertex * vert : allCitys) {
		Node tmp = vert->getInfo();
		cout << TAB << tmp.getNodeID() << " - " << tmp.getCityName() << endl;
	}
	cout << endl;

	cout << "Insira o numero correpondente a cidade que pretende iniciar a viagem, 0 para cancelar: " << endl;
	cin >> idSource;

	if (!cin.good() || idSource> (uint)allCitys.at(allCitys.size() - 1)->getInfo().getNodeID()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido! Tente novamente.");
	}
	if (idSource == 0) return nullptr;


	Vertex* source = travelAgencyGraph.getVertex(Node(idSource));
	return source;
}

void TravelAgency::outPut_CustomTrip(const vector < list<Vertex>> &shortestPath, const map<string, uint> &accomTime, string &dateStr, const set <string> &notWantedTypes) {
	int i=1;
	for (list<Vertex> list : shortestPath) {
		cout << TAB << i << "ª Viagem: " << endl << endl;
		map<string,uint>::const_iterator it=accomTime.find(list.front().getInfo().getCityName());
		uint accommodationTime = it->second;
		outPut_TripToOneCity(list, it->second, dateStr, notWantedTypes);
		addDaysToDate(dateStr, it->second);
		i++;
	}
	return;
}

void TravelAgency::tripToMonuments(Vertex* source,const vector<pair<string, int>> &found, const vector <string> cities) 
{
	unsigned int idDest;
	unsigned posChoice;
	Vertex* dest;
	if (found.size() == 1) {
		idDest = found.at(0).second;
		dest = travelAgencyGraph.getVertex(Node(idDest));
	}
	else {
		unsigned posChoice;
		cout << "Insira qual dos monumentos pretende visitar, 0 para cancelar:" << endl;
		for (size_t i = 0; i < found.size(); i++) {
			cout << i + 1 << ". " << found.at(i).first << " - " << cities.at(i) << endl;
		}
		cout << endl;
		cout << "> ";
		cin >> posChoice;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw exception_or_error("O input nao e valido! Tente novamente.");
		}

		if (posChoice == 0)
			return;
		dest = travelAgencyGraph.getVertex(Node(found.at(posChoice-1).second));
	}

	string dateStr;
	cout << "Insira a data em que pretende iniciar a viagem: " << endl;
	cin >> dateStr;
	Date date = Date(dateStr);

	unsigned int accommodationTime;
	cout << "Deseja adquirir alojamento por quanto tempo (0 se não pretender): " << endl;
	cin >> accommodationTime;

	if (!cin.good() || accommodationTime > 60) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido! Tente novamente.");
	}

	set<string> notWantedTypes = load_notWantedTypes();

	list <Vertex> shortestPath;
	if (travelAgencyGraph.shortestPath((*source), (*dest), shortestPath, notWantedTypes) == 0.0) {
		throw exception_or_error("O destino que escolheu e impossivel de alcançar apartir da origem dada");
	}
	clrscr();
	cout << "A sua viagem foi calculada, aqui esta a sua informacao: " << endl << endl;
	outPut_TripToOneCity(shortestPath, accommodationTime, dateStr, notWantedTypes);
	system("Pause");
	clrscr();
	return;
}

void TravelAgency::searchMonumentsCities() {
	string line;

	unsigned int idSource;
	Vertex* source = read_current_city(idSource);

	if (source == nullptr)
		return;

	clrscr();

	cout << BIG_TAB << "Pesquisa de pontos de interesse" << endl << endl;
	cout << "Insira os Pontos de Interesse que pretende visitar, separados por newline e sem acentuacao!" << endl;
	cout << "Para terminar pressione enter sem inserir input" << endl << endl;


	do {
		bool foundMatch = false;
		vector<pair<string, int>> found;
		cout << "> ";

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, line);

		if (line == "")
			continue;

		found = travelAgencyGraph.monumentsSearch(line, foundMatch);

		if (found.size() == 0) {
			cout << TAB << "Nao foram encontrados resultados.";
			continue;
		}

		Node foundID(NULL);
		vector<string> cities;

		for (int i = 0; i < found.size(); i++) {
			foundID = Node(found.at(i).second);
			cities.push_back(travelAgencyGraph.getVertex(foundID)->getInfo().getCityName());
		}

		if (foundMatch)
			cout << endl << TAB << "Foram encontrados " << found.size() << " resultados: " << endl;
		else
			cout << endl << TAB << "Nao foram encontrados resultados exatos para a sua pesquisa, aqui estao os 5 monumentos com o nome mais proximo do seu input:" << endl;

		cout << left << setw(25) << "   Monuments" << "City" << endl;
		for (int i = 0; i < found.size(); i++)
			cout << left << setw(25) << to_string(i + 1) + ". " + found.at(i).first << cities.at(i) << endl;
		cout << endl;

		cout << "Deseja marcar viagem para algum dos destinos apresentados no ecra? (s/y se sim)" << endl;
		cin >> line;
		if (line == "s" || line == "y" || line == "S" || line == "Y") {
			clrscr();
			
			for (size_t i = 0; i < found.size(); i++){
				if (found.at(i).second == source->getInfo().getNodeID()) {
					found.erase(found.begin() + i);
					cities.erase(cities.begin() + i);
				}
			}
			tripToMonuments(source,found,cities);
			clrscr();
			cout << BIG_TAB << "Pesquisa de pontos de interesse" << endl << endl;
			cout << "Insira os Pontos de Interesse que pretende visitar, separados por newline e sem acentuacao!" << endl;
			cout << "Para terminar pressione enter sem inserir input" << endl << endl;
		}

	} while (line != "");


	system("Pause");
	clrscr();
	return;
}


