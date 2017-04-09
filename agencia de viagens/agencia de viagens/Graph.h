#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <set>

#include "Node.h"
#include "Weight.h"

constexpr int NOT_VISITED = 0;
constexpr int BEING_VISITED = 1;
constexpr int DONE_VISITED = 2;
constexpr int INT_INFINITY = INT_MAX;

class Graph;
class Vertex;
class Edge;

class Graph
{
public:
	bool addVertex(Node const & info);
	bool addEdge(Node const & src, Node const & dest, Weight weight, int edgeID);
	std::vector<Vertex *> getVertexes() const;
	Vertex * getVertex(Node const & info) const;
	void getPath(Vertex vOrig, Vertex vDest, int *pathKeys, list<Vertex> &path);
	double shortestPath(Vertex vOrig, Vertex vDest, list<Vertex> &shortPath, const set<string> &notWantedTypes);
	void shortestPathLength(Vertex vOrig, bool *visited, int *pathKeys, double* dist,const set<string> &notWantedTypes);
	void customTripAlgorithm(vector<Vertex> &visited, vector<Vertex> &toVisit, vector < list <Vertex> > &shortestPath, const set<string> &notWantedTypes);
private:
	std::vector<Vertex *> vertexes;
};

class Vertex
{
public:
	void addEdgeTo(Vertex * dest, Weight weight, int edgeID);
	Node getInfo() const;
	std::vector<Edge> getEdges() const;
	Vertex(Node info);
private:
	Node info;
	std::vector<Edge> edges;
	int indegree;
	friend class Graph;
};

class Edge
{
public:
	int getID() const;
	double getLowestWeight(set<string> const & notWantedTypes);
	Vertex * getDest() const;
	Weight  getWeight() const;


	Edge(Vertex * dest, Weight weight, int edgeID);
private:
	int ID;
	Vertex * dest;
	Weight weight;

	friend class Graph;
	friend class Vertex;
};

#endif