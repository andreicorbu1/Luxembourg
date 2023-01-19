#include "Node.h"

Node::Node(double x, double y, int info) : m_coords(QPointF(x,y)), m_id(info)
{}

Node::Node(int info) : m_id(info)
{}

void Node::SetID(int id)
{
	this->m_id = id;
}

void Node::SetCoords(QPointF coords)
{
	this->m_coords = coords;
}

int Node::GetInfo() const
{
	return m_id;
}

QPointF Node::GetCoords() const
{
	return m_coords;
}

bool Node::operator==(const Node& rhs) const
{
	return m_id == rhs.m_id && m_coords == rhs.m_coords;
}

bool Node::operator!=(const Node& rhs) const
{
	return !(*this == rhs);
}

bool Node::operator<(const Node& rhs) const
{
	return m_id < rhs.m_id;
}

bool Node::operator>(const Node& rhs) const
{
	return m_id > rhs.m_id;
}

Node& Node::operator=(const Node& rhs)
{
	m_id = rhs.m_id;
	m_coords.setX(rhs.m_coords.x());
	m_coords.setY(rhs.m_coords.y());
	return *this;
}

double Node::operator-(const Node & rhs) const
{
	return sqrt(
		((m_coords.x() - rhs.m_coords.x()) * (m_coords.x() - rhs.m_coords.x())) + ((m_coords.y() - rhs.m_coords.y()) * (m_coords.y() - rhs.m_coords.y()))
	);
}
