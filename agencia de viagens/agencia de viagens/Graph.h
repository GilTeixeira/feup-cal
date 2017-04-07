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
	bool removeVertex(Node const & info);
	bool removeEdge(Node const & src, Node const & dest);
/*	std::vector<Node> dfs() const;
	std::vector<Node> bfs(Vertex * v) const;
	int maxNewChildren(Vertex * v, Node & info) const;*/
	/*
	
	int getNumVertex() const;*/
	std::vector<Vertex *> getVertexes() const;
	
	Vertex * getVertex(Node const & info) const;
	void resetIndegrees();
/*	std::vector<Vertex *> getSources() const;
	int getNumCycles();
	bool isDAG();
	std::vector<Node> topologicalOrder();*/
	std::vector<Node> getPath(Node const & src, Node const & dest);

	void unweightedShortestPath(Node const & info);
//	void dijkstraShortestPath(Node const & dest, string dateStr, set<string> const & notWantedTypes);
	std::vector<Node> getLowestPricePath(Node const & src, Node const & dest, string dateStr, set<string> const & notWantedTypes);
private:
	int numCycles;
	std::vector<Vertex *> vertexes;
	/*
	void dfs(Vertex * v, std::vector<Node> & res) const;
	void dfsVisit(Vertex * v);	
	void dfsVisit();
	void getPathTo(Vertex * dest, std::list<Node> & res);*/
};

class Vertex
{
public:
	void addEdgeTo(Vertex * dest, Weight weight, int edgeID);
	bool removeEdgeTo(Vertex * dest);
	Node getInfo() const;
	int getIndegree() const;
	std::vector<Edge> getEdges() const;
	double getWDistance() const;

	Vertex(Node info);
private:
	Vertex * path;
	Node info;
	std::vector<Edge> edges;

	int indegree;
	int distance;
	double weight_distance;

	bool visited;
	bool processing;

	friend class Graph;
};

class Edge
{
public:
	int getID() const;
	double getLowestWeight(string & dateStr, set<string> const & notWantedTypes);
	Vertex * getDest() const;

	Edge(Vertex * dest, Weight weight, int edgeID);
private:
	int ID;
	Vertex * dest;
	Weight weight;

	friend class Graph;
	friend class Vertex;
};

#endif