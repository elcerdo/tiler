#include "selectionitem.h"

#include <QDebug>
#include <QPen>
#include <QBrush>
#include <cmath>

QPoint SelectionItem::quantizePoint(const QPointF &point)
{
    const int x = round(point.x()/24);
    const int y = round(point.y()/24);
    return QPoint(x,y);
}
    
SelectionItem::SelectionItem(QObject* parent)
    : QObject(parent), QGraphicsRectItem(0,0,24,24,NULL), start_position(0,0)
{
    static QPen pen;
    pen.setColor(Qt::black);
    pen.setWidthF(2);

    static QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::Dense5Pattern);

    setPen(pen);
    setBrush(brush);
}

void SelectionItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    start_position = event->pos();
    qDebug() << "click" << start_position << quantizePoint(start_position);
    event->accept();
}


void SelectionItem::handleTranslation(const QPointF &position)
{
    const QPoint translation = quantizePoint(position);
    if (translation.isNull()) return;
    qDebug() << "moving selection" << pos() << translation;
    emit movedFrom(QPoint(std::floor(pos().x()/24),std::floor(pos().y()/24)));
    moveBy(translation.x()*24,translation.y()*24);
    //setPos(selection_position);
}

void SelectionItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "release" << event->pos() << quantizePoint(event->pos());
    handleTranslation(event->pos()-start_position);
    event->accept();
}

void SelectionItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //qDebug() << "move" << event->pos() << quantizePoint(event->pos());
    handleTranslation(event->pos()-start_position);
    event->accept();
}
