#include "Graph.h"

bool Graph::addVertex(Node const & info)
{
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		if ((*it)->info == info)
		{
			return false;
		}
	}
	vertexes.push_back(new Vertex(info));
	return true;
}
bool Graph::addEdge(Node const & src, Node const & dest, Weight weight, int edgeID)
{
	auto it = vertexes.begin(), it_e = vertexes.end();
	int found = 0;
	Vertex * vS, *vD;
	while (found != 2 && it != it_e)
	{
		if ((*it)->info == src)
		{
			vS = *it;
			++found;
		}
		if ((*it)->info == dest)
		{
			vD = *it;
			++found;
		}
		++it;
	}
	if (found != 2)
	{
		return false;
	}
	++(vD->indegree); 
	vS->addEdgeTo(vD, weight, edgeID);
	return true;
}

std::vector<Vertex *> Graph::getVertexes() const
{
	return vertexes;
}

Vertex * Graph::getVertex(Node const & info) const
{
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		if ((*it)->info == info)
		{
			return *it;
		}
	}
	return nullptr;
}

void Graph::getPath(Vertex vOrig, Vertex vDest, int *pathKeys, list<Vertex> &path)
{

	if (vOrig.getInfo() != vDest.getInfo()) {
		path.push_back(vDest);
		int vKey = vDest.getInfo().getNodeID()-1;
		int prevVKey = pathKeys[vKey];
		vDest = (*vertexes[prevVKey]);

		getPath(vOrig, vDest, pathKeys, path);
	}
	else {
		path.push_back(vOrig);
	}
}

double Graph::shortestPath(Vertex vOrig, Vertex vDest, list<Vertex> &shortPath,const set<string> &notWantedTypes) {
	size_t nverts = vertexes.size();
	bool * visited= new bool[nverts]; 
	int *pathKeys = new int[nverts];
	double *dist = new double[nverts];


	for (int i = 0; i < nverts; i++) {
		dist[i] = numeric_limits<double>::max();
		pathKeys[i] = -1;
		visited[i] = false;
	}

	shortestPathLength(vOrig, visited, pathKeys, dist, notWantedTypes);

	double lengthPath = dist[vDest.getInfo().getNodeID()-1];

	if (lengthPath != numeric_limits<double>::max()) {
		getPath(vOrig, vDest, pathKeys, shortPath);
		return lengthPath;
	}
	return 0;
}

void  Graph::shortestPathLength(Vertex vOrig, bool *visited,int *pathKeys, double* dist, const set<string> &notWantedTypes) {
	int vkey = vOrig.getInfo().getNodeID()-1;
	dist[vkey] = 0;
 	while (vkey != -1) {
		vOrig = (*vertexes[vkey]);
		visited[vkey] = true;
		for (Edge edge : vOrig.getEdges()) {
			Vertex vAdj =(*edge.getDest());
			int vkeyAdj = edge.getDest()->getInfo().getNodeID()-1;
			if (!visited[vkeyAdj] && dist[vkeyAdj] > dist[vkey] + edge.getLowestWeight(notWantedTypes)) {
				dist[vkeyAdj] = dist[vkey] + edge.getLowestWeight(notWantedTypes);
				pathKeys[vkeyAdj] = vkey;
			}
		}
		double minDist = numeric_limits<double>::max();
		vkey = -1;
		for (int i = 0; i < vertexes.size(); i++) {
			if (!visited[i] && dist[i] < minDist) {
				minDist = dist[i];
				vkey = i;
			}
		}
	}
}






void Vertex::addEdgeTo(Vertex * dest, Weight weight, int edgeID)
{
	edges.emplace_back(dest, weight, edgeID);
}

Node Vertex::getInfo() const
{
	return info;
}
Vertex::Vertex(Node info) :  info(info), indegree(0)
{
}

std::vector<Edge> Vertex::getEdges() const {
	return edges;
}

int Edge::getID() const
{
	return ID;
}
double Edge::getLowestWeight( set<string> const & notWantedTypes)
{
	TripInfo trip = weight.getEdgeWeightPrice(notWantedTypes);
	return trip.getPrice();
}

Vertex * Edge::getDest() const {
	return dest;

}
Weight Edge::getWeight() const
{
	return weight;
}
Edge::Edge(Vertex * dest, Weight weight, int edgeID) : ID(edgeID), dest(dest), weight(weight)
{
}


void Graph::customTripAlgorithm(vector<Vertex>& visited, vector<Vertex>& toVisit,
	vector<list<Vertex>>& shortestPathList, const set<string>& notWantedTypes)
{
	while (!toVisit.empty()) {
		size_t posToVisited;
		list<Vertex> shortPath;
		list<Vertex> bestPath;
		double bestprice = numeric_limits<double>::max();
		for (size_t i = 0; i < toVisit.size(); i++) {
			shortPath.clear();
			Vertex visit = toVisit.at(i);

			double currentprice = shortestPath(visited.at(visited.size() - 1), visit
				, shortPath, notWantedTypes);

			if (currentprice == 0) throw exception_or_error("Os nossos transportes nao tem maneira de alcancar um dos destinos que escolheu");

			if (bestprice > currentprice) {
				bestprice = currentprice;
				bestPath = shortPath;
				posToVisited = i;
			}
		}
		shortestPathList.push_back(bestPath);
		visited.push_back(toVisit.at(posToVisited));
		toVisit.erase(toVisit.begin() + posToVisited);
	}
	return;
}

vector<pair<string, int>> Graph::monumentsSearch(const string &tosearch) const
{
	vector <pair<string, int>> matchingStrings;
	vector <pair<string, int>> approximateStrings;
	vector <int> distance;
	bool foundMatch = false;


	for (size_t node = 0; node < vertexes.size(); node++){
		vector<string> monuments = vertexes.at(node)->getInfo().getMonuments();
		for (size_t mnmts = 0; mnmts < monuments.size(); mnmts++) {
			string monumentFound = monuments.at(mnmts);
			int idNodeFound = vertexes.at(node)->getInfo().getNodeID();
			if (kmp(monuments.at(mnmts), tosearch)) {
				matchingStrings.push_back(make_pair(monumentFound,idNodeFound));
				foundMatch = true;
			}
			if (!foundMatch) {
				includeOnVectorApproximateMatching(approximateStrings, distance, tosearch, monumentFound, idNodeFound);
			}
		}
	}

	if(foundMatch)
		return matchingStrings;

	return approximateStrings;
}

void Graph::includeOnVectorApproximateMatching(vector <pair<string, int>> &approximateStrings, vector <int> &distance,
	const string &toSearch, const string &monumentFound,const int &idNodeFound) const
{
	int dist = editDistance(monumentFound, toSearch);

	if (dist > distance.at(4))
		return;

	size_t i = 0;

	for (i; i < distance.size(); i++) {
		if (dist < distance.at(i)) {
			distance.insert(distance.begin() + i, dist);
			approximateStrings.insert(approximateStrings.begin() + i, make_pair(monumentFound, idNodeFound));
			if(approximateStrings.size()>5){
				distance.pop_back();
				approximateStrings.pop_back();
			}
			break;
		}
	}

	return;
}
