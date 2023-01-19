#pragma once
#include "Node.h"
class Edge
{
public:
	Edge() = default;
	Edge(const Node& first, const Node& second, int cost);
	Node GetFirstNode() const;
	Node GetSecondNode() const;
	int GetCost() const;
	bool operator==(const Edge& rhs) const;
private:
	Node m_firstNode, m_secondNode;
	int m_cost;
};

