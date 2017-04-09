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
	/**
	*@brief  Adds Edge to Another Node.
	*@param dest The Vertex to which the Edge is pointed.
	*@param weight The Weight of the Edge.
	*@param edgeID Edge's ID.
	*/
	void addEdgeTo(Vertex * dest, Weight weight, int edgeID);

	/**
	*@brief Gets Node's Information.
	*@return Node's Information.
	*/
	Node getInfo() const;

	/**
	*@brief Gets All Edges from this Vertex.
	*@return All Edges from this Vertex.
	*/
	std::vector<Edge> getEdges() const;

	/**
	*@brief  Creates an Vertex.
	*@param info The Vertex information.
	*/
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
	/**
	*@brief Gets Edge's ID.
	*@return Edge's ID.
	*/
	int getID() const;

	/**
	*@brief Gets Trip with the lowest the price, which doesnt include not Wanted types.
	*@param notWantedTypes Types of tranportation to be ignored.
	*@return The trip with the lowest price.
	*/
	double getLowestWeight(set<string> const & notWantedTypes);

	/**
	*@brief Gets Edge's Destination.
	*@return Edge's ID.
	*/
	Vertex * getDest() const;

	/**
	*@brief Gets Edge's Weight.
	*@return Edge's ID.
	*/
	Weight  getWeight() const;

	/**
	*@brief  Creates an Edge with pointer to Node, Weight and edgeID as parameters.
	*@param dest The Vertex  to which the Edges is pointed.
	*@param weight The Weight of the Edge.
	*@param edgeID Edge's ID.
	*/
	Edge(Vertex * dest, Weight weight, int edgeID);
private:
	int ID;
	Vertex * dest;
	Weight weight;

	friend class Graph;
	friend class Vertex;
};

#endif