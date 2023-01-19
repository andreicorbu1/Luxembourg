#pragma once
#include <qpoint.h>
class Node
{
public:
	Node(double x, double y, int info = -1);
	Node(int info = -1);
	void SetID(int id);
	void SetCoords(QPointF coords);
	int GetInfo() const;
	QPointF GetCoords() const;
	bool operator == (const Node& rhs) const;
	bool operator!=(const Node& rhs) const;
	double operator-(const Node& rhs) const;
	bool operator<(const Node& rhs) const;
	bool operator>(const Node& rhs) const;
	Node& operator=(const Node& rhs);
private:
	QPointF m_coords;
	int m_id;
};

