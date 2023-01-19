#include "Luxembourg.h"

Luxembourg::Luxembourg(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label->hide();
	ui.label_2->hide();
	ui.label_3->hide();
	m_graph.Construct();
	update();
}
Luxembourg::~Luxembourg()
{}

void Luxembourg::on_pushButton_clicked()
{
	m_nodes.clear();
	start = Node();
	m_graph.Clear();
	isFirstNode = false;
	update();
}

void Luxembourg::paintEvent(QPaintEvent* p)
{
	QPen pen;
	pen.setColor(Qt::black);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(pen);
	DrawEdges(painter, pen);
	if (m_nodes.size() <= 2)
	{
		DrawNodes(painter);
	}
	else
	{
		m_nodes.erase(m_nodes.begin(), m_nodes.begin() + 2);
		DrawNodes(painter);
	}
	if (m_graph.GetFinished())
	{
		painter.setPen(pen);
		DrawPath(painter);
	}
}

void Luxembourg::mousePressEvent(QMouseEvent* ev)
{
	QPainter painter(this);
	QBrush brush;
	brush.setColor(Qt::darkGreen);
	painter.setBrush(brush);
	painter.setRenderHint(QPainter::Antialiasing);
	if (ev->button() == Qt::LeftButton && !isFirstNode)
	{
		m_graph.Clear();
		start.SetCoords(ev->position());
		start = SearchClosestNode(start);
		std::string labelText = "Start Node = " + std::to_string(start.GetInfo());
		QString text = QString::fromUtf8(labelText.c_str());
		ui.label->setText(text);
		ui.label->show();
		m_nodes.push_back(start);
		isFirstNode = true;
	}
	else if (ev->button() == Qt::RightButton && isFirstNode)
	{
		Node seek;
		seek.SetCoords(ev->position());
		end = SearchClosestNode(seek);
		std::string labelText = "End Node = " + std::to_string(end.GetInfo());
		QString text = QString::fromUtf8(labelText.c_str());
		ui.label_2->setText(text);
		ui.label_2->show();
		m_nodes.push_back(end);
		qDebug() << start.GetInfo() << "->" << end.GetInfo() << "\n";
		isFirstNode = false;
		int cost = m_graph.Dijkstra(start, end);
		std::string aux = "Total cost = ";
		aux += std::to_string(cost);
		text = QString::fromUtf8(aux);
		ui.label_3->setText(text);
		ui.label_3->show();
		update();
	}
}

Node Luxembourg::SearchClosestNode(Node seek)
{
	double distance = std::numeric_limits<double>::max();
	Node ans;
	for (Node& node : m_graph.GetNodes())
	{
		if ((seek - node) < distance)
		{
			distance = node - seek;
			ans = node;
		}
	}
	return ans;
}

void Luxembourg::DrawNode(QPainter& painter, const Node& node)
{
	painter.drawEllipse(node.GetCoords(), 15, 15);
	update();
}

void Luxembourg::DrawNodes(QPainter& painter)
{
	painter.setBrush(QBrush(qRgb(5, 200, 247)));
	for (const Node& node : m_nodes)
	{
		painter.drawEllipse(node.GetCoords(), 5, 5);
	}
	update();
}

void Luxembourg::DrawPath(QPainter& painter)
{
	QPen pen;
	pen.setColor(qRgb(5, 200, 247));
	pen.setWidth(3);
	painter.setPen(pen);
	const auto& path = m_graph.GetPath();
	Node current = end;
	while (path.find(current) != path.end() && path.find(current)->second != Node())
	{
		Node next = path.at(current);
		if (current != Node() && next != Node())
		{
			painter.drawLine(next.GetCoords(), current.GetCoords());
			if (next == start)
			{
				return;
			}
			current = next;
		}
	}
	update();
}

void Luxembourg::DrawEdges(QPainter& painter, const QPen& pen)
{
	const std::vector<Edge> edges = m_graph.GetEdges();
	painter.setPen(pen);
	for (const Edge& edge : edges)
	{
		QPointF p1 = edge.GetFirstNode().GetCoords();
		QPointF p2 = edge.GetSecondNode().GetCoords();
		painter.drawLine(p1, p2);
	}
	update();
}
