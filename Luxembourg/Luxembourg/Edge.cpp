#include "Edge.h"

Edge::Edge(const Node& first, const Node& second, int cost) : m_firstNode(first), m_secondNode(second), m_cost(cost)
{}

Node Edge::GetFirstNode() const
{
    return m_firstNode;
}

Node Edge::GetSecondNode() const
{
    return m_secondNode;
}

int Edge::GetCost() const
{
    return m_cost;
}

bool Edge::operator==(const Edge& rhs) const
{
    if (m_firstNode.GetCoords() == rhs.m_firstNode.GetCoords() && m_secondNode.GetCoords() == rhs.m_secondNode.GetCoords())
        return true;
    return false;
}
