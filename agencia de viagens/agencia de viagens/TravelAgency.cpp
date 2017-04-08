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

	Vertex* source = travelAgencyGraph.getVertex(Node(idSource, "", 0, 0, 0));
	Vertex* dest = travelAgencyGraph.getVertex(Node(idDest, "", 0, 0, 0));

	cout << "Insira a data em que pretende iniciar a viagem: " << endl;
	cin >> dateStr;


	cout << "Deseja adquirir alojamento por quanto tempo (0 se não pretender): " << endl;
	cin >> accommodationTime;

	if (!cin.good()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido! Tente novamente.");
	}
	
	notWantedTypes= load_notWantedTypes();

	list <Vertex> shortestPath;
	if (travelAgencyGraph.shortestPath((*source), (*dest), shortestPath, notWantedTypes) == 0.0) {
		throw exception_or_error("O destino que escolheu e impossivel de alcançar apartir da origem dada");
	}
	outPut_TripToOneCity(shortestPath, accommodationTime, dateStr, notWantedTypes);
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
	clrscr();

	list<Vertex>::const_iterator it_i = shortestPath.end();
	list<Vertex>::const_iterator it_f = shortestPath.begin();
	it_i--;

	cout << "A sua viagem foi calculada, aqui esta a sua informacao: " << endl << endl;
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
		system("Pause");
	}
}




