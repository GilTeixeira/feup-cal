#include <cstdio>
#include "FichaJUNG.h"
#include "graphviewer.h"
#include "TravelAgency.h"
#include <fstream>
#include <iostream>
#include <sstream>


void graphviewer(TravelAgency& travelAgencyGraph) {
	vector<Vertex *> nodesToDisplay = travelAgencyGraph.travelAgencyGraph.getVertexes();

	typename vector<Vertex *>::const_iterator it = nodesToDisplay.begin();
	typename vector<Vertex *>::const_iterator ite = nodesToDisplay.end();


	GraphViewer *gv = new GraphViewer(MAP_WIDTH, MAP_HEIGHT, false);
	gv->setBackground("BackGround.jpg");
	gv->createWindow(MAP_WIDTH, MAP_HEIGHT);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");


	//Display  Nodes
	for (; it != ite; it++) {
		pair<int, int> coordGraph = CoodinatesToMap((*it)->getInfo().getLongitude(), (*it)->getInfo().getLatitude());
		gv->addNode((*it)->getInfo().getNodeID(), coordGraph.first, coordGraph.second);
		gv->setVertexLabel((*it)->getInfo().getNodeID(), (*it)->getInfo().getCityName());
	}

	it = nodesToDisplay.begin();

	//Display Edges
	for (; it != ite; it++) {
		vector<Edge> EdgesNode = (*it)->getEdges();

		typename vector<Edge>::const_iterator adj = EdgesNode.begin();
		typename vector<Edge>::const_iterator adje = EdgesNode.end();


		for (; adj != adje; adj++) {
			//Vertex* dest = (*adj).getDest();
			gv->addEdge((*adj).getID(), (*it)->getInfo().getNodeID(), ((*adj).getDest())->getInfo().getNodeID(), EdgeType::DIRECTED);
			//gv->setEdgeLabel();
		}

	}
}
