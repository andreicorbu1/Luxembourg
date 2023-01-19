#pragma once
#include "Edge.h"
#include <string>
#include <fstream>
#include <vector>
#include <QtXml>
#include <QDebug>
#include <qfile.h>
#include <queue>
#include <boost/functional/hash.hpp>

template<>
struct std::hash<Node>
{
	size_t operator()(const Node& other) const
	{
		using boost::hash_value;
		using boost::hash_combine;
		size_t seed = 0;
		hash_combine(seed, hash_value(other.GetInfo()));
		hash_combine(seed, hash_value(other.GetCoords().x()));
		hash_combine(seed, hash_value(other.GetCoords().y()));
		return seed;
	}
};
class Graph
{
public:
	Graph() = default;
	void AddNode(const Node& node);
	void AddEdge(const Edge& edge);
	std::vector<Node> GetNodes() const;
	std::vector<Edge> GetEdges() const;
	bool GetFinished() const;
	Node findNodeById(int id)
	{
		for (const auto& node : m_nodes)
		{
			if (node.GetInfo() == id)
				return node;
		}
	}
	void Construct();
	int Dijkstra(Node start, Node end);
	std::vector<Edge> GetConnectionsOfCurrNode(const Node& node);
	std::unordered_map<Node, Node> GetPath();
	void Clear();
private:
	bool finished = false;
	std::vector<Node> m_nodes;
	std::vector<Edge> m_edges;
	std::unordered_map<Node, Node> cameFrom;
};

