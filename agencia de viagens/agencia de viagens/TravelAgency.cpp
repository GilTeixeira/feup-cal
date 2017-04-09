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
		Node source = Node(sourceID,"", Accommodation(0.0),0,0);
		Node dest = Node(destID,"", Accommodation(0.0),0,0);
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
	if (allCitys.size() == 0) throw exception_or_error("O grafo não contém nenhuma informação verifique o ficheiro de texto.");

	cout << BIG_TAB << "Assitente de Viagem" << endl << endl;

	for (Vertex * vert : allCitys) {
		Node tmp = vert->getInfo();
		cout << TAB << tmp.getNodeID() << " - " << tmp.getCityName()<< endl;
	}
	cout << endl;
	
	cout << "Insira o numero correpondente a cidade que pretende iniciar a viagem, 0 para cancelar: " << endl; 
	cin >> idSource;

	if (!cin.good()|| idSource> (uint) allCitys.at(allCitys.size()-1)->getInfo().getNodeID()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido! Tente novamente.");
	}
	if (idSource == 0) return;
	
	cout << "Insira o numero correpondente a cidade que pretende visitar, 0 para cancelar: " << endl;
	cin >> idDest;

	if (!cin.good() || idDest > (uint)allCitys.at(allCitys.size() - 1)->getInfo().getNodeID()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido! Tente novamente.");
	}

	if (idDest == 0) return;
	if (idSource == idDest) throw ("Escolheu a mesma cidade para a origem e o seu destino!");

	Vertex* source = travelAgencyGraph.getVertex(Node(idSource, "", 0, 0, 0));
	Vertex* dest = travelAgencyGraph.getVertex(Node(idDest, "", 0, 0, 0));

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

	unsigned int idSource, idDest, accommodationTime;
	vector<Vertex> visited;
	vector<Vertex> toVisit;
	map<string,uint> accomTime;

	set <string> notWantedTypes;
	string dateStr;


	vector <Vertex *> allCitys = travelAgencyGraph.getVertexes();
	if (allCitys.size() == 0) throw exception_or_error("O grafo não contém nenhuma informação verifique o ficheiro de texto.");
	
	cout << BIG_TAB << "Assitente de Viagem" << endl << endl;

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
	if (idSource == 0) return;

	Vertex* source = travelAgencyGraph.getVertex(Node(idSource, "", 0, 0, 0));
	visited.push_back((*source));

	while (true) {
		cout << "Insira o numero correpondente a uma das cidades que pretende visitar, 0 se ja inseriu todas as pretendidadas: " << endl;
		cin >> idDest;

		if (!cin.good() || idDest > (uint)allCitys.at(allCitys.size() - 1)->getInfo().getNodeID()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw exception_or_error("O input nao e valido! Tente novamente.");
		}

		if (idDest == 0) break;
		if (idSource == idDest) throw ("Escolheu a mesma cidade para a origem e para um dos seus destinos!");
		
		for (Vertex checkingDup: toVisit) {
			if (checkingDup.getInfo().getNodeID() == idDest) 
				throw ("Nao pode escolher o mesmo destino mais que uma vez!");
		}

		cout << "Deseja adquirir alojamento por quanto tempo nesta cidade (0 se não pretender): " << endl;
		cin >> accommodationTime;

		if (!cin.good()||accommodationTime>60) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw exception_or_error("O input nao e valido! Tente novamente.");
		}

		Vertex* dest = travelAgencyGraph.getVertex(Node(idDest, "", 0, 0, 0));
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


