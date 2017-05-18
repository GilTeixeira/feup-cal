#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <set>

#include "Node.h"
#include "Weight.h"
#include "StringAlgorithms.h"

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
	/**
	*@brief adds a vertex to the graph with the specified info
	*@param info indo of the vertex
	*@return bool true if added the vertex with success false otherwise
	*/
	bool addVertex(Node const & info);
	/**
	*@brief adds an edge to a specfied vertex
	*@param src info of the vertex to add the edge
	*@param dest info of the vertex wich the edge goes to
	*@param wieght weight of the edge
	*@param edgeID edgeID
	*@return bool true if added the edge with success false otherwise
	*/
	bool addEdge(Node const & src, Node const & dest, Weight weight, int edgeID);
	/**
	*@brief return all the vertexes
	*@param info Info to search on the Vertexes
	*@return Vertex* vertex that contains the info
	*/
	std::vector<Vertex *> getVertexes() const;
	/**
	*@brief gets the vertex with the specified info
	*@param info Info to seach on the Vertexes
	*@return Vertex* vertex that contains the info
	*/
	Vertex * getVertex(Node const & info) const;
	/**
	* Extracts from pathKeys the minimum path between vOrig and vDest The path
	* is constructed from the end to the beginning
	*
	* @param vOrig information of the Vertex origin
	* @param vDest information of the Vertex destination
	* @param pathkeys minimum path vertices keys
	* @param path stack with the minimum path (correct order)
	*/
	void getPath(Vertex vOrig, Vertex vDest, int *pathKeys, list<Vertex> &path);
	/**
	* Dijkstra's Algorithm to calculate the shortest path beetween vOrig, vDest
	* @param vOrig information of the Vertex origin
	* @param vDest information of the Vertex destination
	* @param shortespath stack with the minimum path (correct order)
	* @param notWantedTypes tranportation types that the user doens't want to use
	* @return double total weight of the shortestPath
	*/
	double shortestPath(Vertex vOrig, Vertex vDest, list<Vertex> &shortPath, const set<string> &notWantedTypes);
	/**
	* Computes shortest-path distance from a source vertex to all reachable
	* vertices of a graph g with nonnegative edge weights This implementation
	* uses Dijkstra's algorithm
	*
	* @param vOrig Vertex that will be the source of the path
	* @param visited set of discovered vertices
	* @param pathkeys minimum path vertices keys
	* @param dist minimum distances
	* @param notWantedTypes tranportation types that the user doens't want to use
	*/
	void shortestPathLength(Vertex vOrig, bool *visited, int *pathKeys, double* dist, const set<string> &notWantedTypes);
	/**
	*Greedy Algorithm that uses the dijkstra algorithm to calculate the shortesPath beetween two citys
	and uses that information to create a custom trip to various destinations given a starting point
	* @param visited information of the Vertex origin
	* @param toVisit information of all the Vertex destinations
	* @param shortespath list of stacks with the minimum path
	* @param notWantedTypes tranportation types that the user doens't want to use
	*/
	void customTripAlgorithm(vector<Vertex> &visited, vector<Vertex> &toVisit, vector < list <Vertex> > &shortestPath, const set<string> &notWantedTypes);

	/**
	*
	*/
	vector<pair<string,int>> monumentsSearch(const string &tosearch) const;



private:
	std::vector<Vertex *> vertexes;
	/**
	*
	*/
	void includeOnVectorApproximateMatching(vector <pair<string, int>> &approximateStrings, vector <int> &distance, const string &toSearch, const string &monumentFound, const int &idNodeFound) const;
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