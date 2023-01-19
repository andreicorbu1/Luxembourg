#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Luxembourg.h"
#include "Graph.h"
#include <QMouseEvent>
#include <qpainter.h>
#include <limits>
class Luxembourg : public QMainWindow
{
	Q_OBJECT

public:
	Luxembourg(QWidget* parent = nullptr);
	~Luxembourg();
	void paintEvent(QPaintEvent* p) override;
	void mousePressEvent(QMouseEvent* ev) override;
	Node SearchClosestNode(Node seek);

private slots:
	void on_pushButton_clicked();

private:
	void DrawNode(QPainter& painter, const Node& node);
	void DrawNodes(QPainter& painter);
	void DrawPath(QPainter& painter);
	void DrawEdges(QPainter& painter, const QPen& pen);
	Ui::LuxembourgClass ui;
	Graph m_graph;
	std::vector<Node> m_nodes;
	Node start;
	Node end;
	bool isFirstNode = false;
};
