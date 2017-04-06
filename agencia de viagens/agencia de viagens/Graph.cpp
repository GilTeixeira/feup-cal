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
	++(vD->indegree); //adicionado pelo exercicio 5
	vS->addEdgeTo(vD, weight, edgeID);
	return true;
}
bool Graph::removeVertex(Node const & info)
{
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		if ((*it)->info == info)
		{	//se encontrar
			Vertex * tmp = *it; //guarda temporario
			vertexes.erase(it); //apaga
			for (it = vertexes.begin(); it != it_e; ++it)
			{
				(*it)->removeEdgeTo(tmp);
			}
			// decrementa indegree para arestas que se iniciam em "v"
			for (auto it = tmp->edges.begin(), it_e = tmp->edges.end(); it != it_e; ++it)
			{
				--(it->dest->indegree);
			}
			delete tmp;
			return true;
		}
	}
	return false;
}
bool Graph::removeEdge(Node const & src, Node const & dest)
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
	return vS->removeEdgeTo(vD);
}/*
std::vector<Node> Graph::dfs() const
{
	auto it = vertexes.begin(), it_e = vertexes.end();
	while (it != it_e)
	{
		(*it++)->visited = false;
	}
	std::vector<Node> res;
	for (it = vertexes.begin(); it != it_e; ++it)
	{
		if ((*it)->visited == false)
		{
			dfs(*it, res);
		}
	}
	return res;
}
std::vector<Node> Graph::bfs(Vertex * v) const
{
	std::vector<Node> res;
	std::queue<Vertex *> queue;
	queue.push(v);
	v->visited = true;
	while (!queue.empty())
	{
		Vertex * vt = queue.front();
		queue.pop();
		res.push_back(vt->info);
		for (auto it = vt->edges.begin(), it_e = vt->edges.end(); it != it_e; ++it)
		{
			Vertex * dest = it->dest;
			if (dest->visited == false)
			{
				dest->visited = true;
				queue.push(dest);
			}
		}
	}
	return res;
}
int Graph::maxNewChildren(Vertex * v, Node & info) const
{
	std::vector<Node> res;
	std::queue<Vertex *> queue;
	std::queue<int> level;
	int maxChildren = 0;
	info = v->info;
	queue.push(v);
	level.push(0);
	v->visited = true;
	while (!queue.empty())
	{
		Vertex * vt = queue.front();
		queue.pop();
		res.push_back(vt->info);
		int lt = level.front();
		level.pop();
		++lt;
		int nChildren = 0;

		for (auto it = vt->edges.begin(), it_e = vt->edges.end(); it != it_e; ++it)
		{
			Vertex * dest = it->dest;
			if (dest->visited == false)
			{
				dest->visited = true;
				queue.push(dest);
				level.push(lt);
				++nChildren;
			}
		}
		if (nChildren > maxChildren)
		{
			maxChildren = nChildren;
			info = vt->info;
		}
	}
	return maxChildren;
}
int Graph::getNumVertex() const
{
return vertexes.size();
}
*/
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
}/*
void Graph::resetIndegrees()
{
	//colocar todos os indegree em 0;
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		(*it)->indegree = 0;
	}

	//actualizar os indegree
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		//percorrer o vetor de Edges, e atualizar indegree
		for (auto e_it = (*it)->edges.begin(), e_it_e = (*it)->edges.end(); e_it != e_it_e; ++e_it)
		{
			++(e_it->dest->indegree);
		}
	}
}
std::vector<Vertex *> Graph::getSources() const
{
	std::vector<Vertex *> buffer;
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		if ((*it)->indegree == 0)
		{
			buffer.push_back(*it);
		}
	}
	return buffer;
}
int Graph::getNumCycles()
{
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}
bool Graph::isDAG()
{
	if (getNumCycles() == 0)
	{
		return true;
	}
	return false;
}*//*
std::vector<Node> Graph::topologicalOrder()
{
	//vetor com o resultado da ordenacao
	std::vector<Node> res;

	//verificar se ee um DAG
	if (getNumCycles() > 0)
	{
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	std::queue<Vertex *> queue;

	std::vector<Vertex *> sources = getSources();
	while (!sources.empty())
	{
		queue.push(sources.back());
		sources.pop_back();
	}

	//processar fontes
	while (!queue.empty())
	{
		Vertex * vt = queue.front();
		queue.pop();

		res.push_back(vt->info);

		for (auto it = vt->edges.begin(), it_e = vt->edges.end(); it != it_e; ++it)
		{
			if (--(it->dest->indegree) == 0)
			{
				queue.push(it->dest);
			}
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != vertexes.size())
	{
		while (!res.empty())
		{
			res.pop_back();
		}
	}

	//garantir que os "indegree" ficam atualizados no final
	resetIndegrees();

	return res;
}*/
std::vector<Node> Graph::getPath(Node const & src, Node const & dest)
{
	std::list<Node> buffer;
	Vertex * vt = getVertex(dest);
	buffer.push_front(vt->info);
	while (vt->path->info != src)
	{
		vt = vt->path;
		buffer.push_front(vt->info);
	}
	buffer.push_front(vt->path->info);
	std::vector<Node> res;
	while (!buffer.empty())
	{
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}
void Graph::unweightedShortestPath(Node const & info)
{
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		(*it)->path = nullptr;
		(*it)->distance = INT_INFINITY;
	}

	Vertex * vt = getVertex(info);
	vt->distance = 0;
	std::queue<Vertex *> queue;
	queue.push(vt);

	while (!queue.empty())
	{
		vt = queue.front();
		queue.pop();
		for (auto it = vt->edges.begin(), it_e = vt->edges.end(); it != it_e; ++it)
		{
			Vertex * tmp = it->dest;
			if (tmp->distance == INT_INFINITY)
			{
				tmp->distance = vt->distance + 1;
				tmp->path = vt;
				queue.push(tmp);
			}
		}
	}
}/*
void Graph::dfs(Vertex * v, std::vector<Node> & res) const
{
	v->visited = true;
	res.push_back(v->info);
	for (auto it = (v->edges).begin(), it_e = (v->edges).end(); it != it_e; ++it)
	{
		if (it->dest->visited == false)
		{
			dfs(it->dest, res);
		}
	}
}
void Graph::dfsVisit(Vertex * v)
{
	for (auto it = v->edges.begin(), it_e = v->edges.end(); it != it_e; ++it)
	{
		if (it->dest->processing == true)
		{
			++numCycles;
		}
		if (it->dest->visited == false)
		{
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}
void Graph::dfsVisit()
{
	auto it = vertexes.begin(), it_e = vertexes.end();
	for (; it != it_e; ++it)
	{
		(*it)->visited = false;
	}
	for (it = vertexes.begin(); it != it_e; ++it)
	{
		if ((*it)->visited == false)
		{
			cout << "Being visited" << endl;
			dfsVisit(*it);
		}
	}
}*//*
void Graph::getPathTo(Vertex * dest, std::list<Node> & res)
{
	res.push_back(dest->info);
	if (dest->path)
	{
		getPathTo(dest->path, res);
	}
}*/
std::vector<Node> Graph::getLowestPricePath(Node const & src, Node const & dest, string dateStr, set<string> const & notWantedTypes)
{
	unweightedShortestPath(dest);
	// ===== Custom Dijkstra Algorithm - Needs testing =====
	for (auto it = vertexes.begin(), it_e = vertexes.end(); it != it_e; ++it)
	{
		(*it)->path = nullptr;
		(*it)->weight_distance = INT_INFINITY;
		(*it)->processing = false;
	}

	Vertex * vs = getVertex(src);
	vs->weight_distance = 0;

	std::vector<Vertex *> pqueue;
	pqueue.push_back(vs);

	std::make_heap(pqueue.begin(), pqueue.end());

	while (!pqueue.empty())
	{
		vs = pqueue.front();
		pop_heap(pqueue.begin(), pqueue.end());
		pqueue.pop_back();

		bool distance_constraint = true;
		bool checked = false;

		for (auto it = vs->edges.begin(), it_e = vs->edges.end(); (it != it_e ? true : (checked ? false : (distance_constraint ? distance_constraint = false, it = vs->edges.begin(), true : false))); ++it)
		{
			Vertex * vd = it->dest;
			string nextDateStr = dateStr;
			double edge_weight;
			if (!distance_constraint || vd->distance < vs->distance)
			{
				if (vs->weight_distance + (edge_weight = it->getLowestWeight(nextDateStr, notWantedTypes)) < vd->weight_distance)
				{
					checked = true;
					dateStr = nextDateStr;
					vd->weight_distance = vs->weight_distance + edge_weight;
					vd->path = vs;

					//se já estiver na lista, apenas a actualiza
					if (!vd->processing)
					{
						vd->processing = true;
						pqueue.push_back(vd);
					}

					make_heap(pqueue.begin(), pqueue.end(), [](Vertex * v1, Vertex * v2)
					{
						return v1->getWDistance() > v2->getWDistance();
					});

					if (!distance_constraint) break; // Is this necessary?
				}
			}
		}
	}
	// =====
	return getPath(src, dest);
}

void Vertex::addEdgeTo(Vertex * dest, Weight weight, int edgeID)
{
	edges.emplace_back(dest, weight, edgeID);
}
bool Vertex::removeEdgeTo(Vertex * dest)
{
	for (auto it = edges.begin(), it_e = edges.end(); it != it_e; ++it)
	{
		if (it->dest == dest)
		{
			edges.erase(it);
			return true;
		}
	}
	return false;
}
Node Vertex::getInfo() const
{
	return info;
}
double Vertex::getWDistance() const
{
	return weight_distance;
}
int Vertex::getIndegree() const
{
	return indegree;
}
Vertex::Vertex(Node info) : path(nullptr), info(info), indegree(0), distance(0), weight_distance(0), visited(false), processing(false)
{
}

int Edge::getID() const
{
	return ID;
}
double Edge::getLowestWeight(string & dateStr, set<string> const & notWantedTypes)
{
	TripInfo trip = weight.getEdgeWeightPrice(dateStr, notWantedTypes, dest->getInfo().getAccommodation());
	return trip.getPrice();
}
Edge::Edge(Vertex * dest, Weight weight, int edgeID) : ID(edgeID), dest(dest), weight(weight)
{
}