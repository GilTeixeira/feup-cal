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


void TravelAgency::displayGraph() {
	/*

	vector<Vertex *> nodesToDisplay = travelAgencyGraph.getVertexes();

	typename vector<Vertex *>::const_iterator it = nodesToDisplay.begin();
	typename vector<Vertex *>::const_iterator ite = nodesToDisplay.end();
	

	GraphViewer *gv = new GraphViewer(MAP_WIDTH, MAP_HEIGHT, false);
	gv->setBackground("world.jpg");
	gv->createWindow(MAP_WIDTH, MAP_HEIGHT);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	gv->addNode(0, 30, 30);


	//Display  Nodes
	for (; it != ite; it++) {
		pair<int, int> coordGraph = CoodinatesToMap((*it)->getInfo().getLongitude(), (*it)->getInfo().getLatitude());
		gv->addNode((*it) ->getInfo().getNodeID(), coordGraph.first, coordGraph.second);
	}

	
	//Display  Edges To Do

	*/


}

