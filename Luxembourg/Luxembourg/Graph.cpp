#include "Graph.h"

const int Width = 562;
const int Height = 921;


void Graph::Construct()
{
	QFile file("Harta_Luxemburg.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << "Eroare la parsare";
		exit(-1);
	}
	QXmlStreamReader reader(&file);
	reader.readNext();
	while (!reader.isEndDocument())
	{
		if (reader.isStartElement())
		{
			if (reader.name() == QString("node"))
			{
				int id = reader.attributes().value("id").toInt();
				double x = reader.attributes().value("longitude").toInt();
				double y = reader.attributes().value("latitude").toInt();
				x = (x - 4945029) * (Height + 50 - 20) / (5018275 - 4945029) + 25;
				y = (y - 573929) * (Width + 50 - 20) / (652685 - 573929) + 130;
				m_nodes.emplace_back(y, x, id);
			}
			else
			{
				if (reader.name() == QString("arc"))
				{
					int firstNodeId = reader.attributes().value("from").toInt();
					int secondNodeId = reader.attributes().value("to").toInt();
					int cost = reader.attributes().value("length").toInt();
					Node firstNode, secondNode;
					for (const Node& node : m_nodes)
					{
						if (node.GetInfo() == firstNodeId)
						{
							firstNode = node;
						}
						if (node.GetInfo() == secondNodeId)
						{
							secondNode = node;
						}
					}
					m_edges.emplace_back(firstNode, secondNode, cost);
				}
			}
		}
		reader.readNext();
	}
}

struct comparator
{
	bool operator()(const std::pair<int, Node>& pair1, const std::pair<int, Node>& pair2)
	{
		return pair1.first > pair2.first;
	}
};

int Graph::Dijkstra(Node start, Node end)
{
	cameFrom.clear();
	std::vector<bool> vis(m_nodes.size(), false);
	std::vector<int> dist(m_nodes.size(), 0x3f3f3f3f);
	std::priority_queue <std::pair<int, Node>, std::deque<std::pair<int, Node>>, comparator> pq;
	vis[start.GetInfo()] = false;
	dist[start.GetInfo()] = 0;
	cameFrom[start] = Node();
	pq.push({dist[start.GetInfo()], start});
	finished = false;
	Node current;
	while (!pq.empty())
	{
		do
		{
			current = pq.top().second;
			pq.pop();
		} while (vis[current.GetInfo()] == true);
		vis[current.GetInfo()] = true;
		if (current == end)
		{
			finished = true;
			return dist[end.GetInfo()];
		}
		const auto& vec = GetConnectionsOfCurrNode(current);
		for (const auto& it : vec)
		{
			if (!vis[it.GetSecondNode().GetInfo()])
			{
				Node next = it.GetSecondNode();
				int cost = it.GetCost();
				if (dist[next.GetInfo()] > dist[current.GetInfo()] + cost)
				{
					dist[next.GetInfo()] = dist[current.GetInfo()] + cost;
					pq.push({dist[next.GetInfo()], next});
					cameFrom[next] = current;
				}
			}
		}
	}
	if (finished)
	{
		qDebug() << "Am gasit pathul cel mai scurt";
	}
	else
	{
		qDebug() << "N-am gasit";
		return -1;
	}
}

std::vector<Edge> Graph::GetConnectionsOfCurrNode(const Node& node)
{
	std::vector<Edge> ans;
	for (const auto& edge : m_edges)
	{
		if (edge.GetFirstNode() == node)
		{
			ans.emplace_back(edge);
		}
	}
	return ans;
}

std::unordered_map<Node, Node> Graph::GetPath()
{
	return cameFrom;
}

void Graph::Clear()
{
	finished = false;
	cameFrom.clear();
}

void Graph::AddNode(const Node& node)
{
	m_nodes.push_back(node);
}

void Graph::AddEdge(const Edge& edge)
{
	m_edges.push_back(edge);
}

std::vector<Node> Graph::GetNodes() const
{
	return m_nodes;
}

std::vector<Edge> Graph::GetEdges() const
{
	return m_edges;
}

bool Graph::GetFinished() const
{
	return finished;
}

