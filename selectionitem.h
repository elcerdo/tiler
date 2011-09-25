#ifndef __SELECTIONITEM_H__
#define __SELECTIONITEM_H__

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class SelectionItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
	SelectionItem(QObject* parent=NULL);
    protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

	void handleTranslation(const QPointF &position);

	QPointF start_position;
};

#endif
