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
		string sourceStr, destStr;
		Weight tmpW = read_edge(f, linenum, sourceStr, destStr);
		Node source = Node(sourceStr, Accommodation(0.0));
		Node dest = Node(destStr, Accommodation(0.0));
		travelAgencyGraph.addEdge(source, dest, tmpW);
	}

	read_line(f, linetmp, linenum);
	if (linetmp != "#End")
		throw exception_or_error("O ficheiro esta corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #End");

	f.close();
	return;
}

