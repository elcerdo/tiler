#ifndef __TILEWIDGET_H__
#define __TILEWIDGET_H__

#include <QSet>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "selectionitem.h"

unsigned int qHash(const QPoint& point);
typedef QSet<QPoint> TileMap;

class TileWidget : public QGraphicsView {
    Q_OBJECT
    public:
	TileWidget(QWidget* parent=NULL);
    protected slots:
	void on_selection_movedFrom(const QPoint &point);
    protected:
	static QPoint quantizePoint(const QPointF &point);
	void mousePressEvent(QMouseEvent* event);
	void drawBackground(QPainter* painter,const QRectF& clipping);
	QGraphicsScene* scene;
	SelectionItem* selection;

	TileMap map;
};

#endif

