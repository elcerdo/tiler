#include "tilewidget.h"

#include <QMetaObject>
#include <QGraphicsRectItem>
#include <QDebug>
#include <cmath>
#include <QMouseEvent>

unsigned int qHash(const QPoint& point)
{
    return qHash(QString("%1|%2").arg(point.x()).arg(point.y()));
}

QRectF rectForPosition(const QPoint& point)
{
    return QRectF(point*24,QSizeF(24,24));
}


QPoint TileWidget::quantizePoint(const QPointF &point)
{
    const int x = std::floor(point.x()/24);
    const int y = std::floor(point.y()/24);
    return QPoint(x,y);
}

    TileWidget::TileWidget(QWidget* parent)
: QGraphicsView(parent), scene(NULL)
{
    selection = new SelectionItem(this);
    selection->setObjectName("selection");

    scene = new QGraphicsScene(this);
    scene->addItem(selection);

    setDragMode(QGraphicsView::NoDrag);
    setScene(scene);

    setSceneRect(QRectF(0,0,24,24));
    scale(2,2);
    //fitInView(QRectF(0,0,240,240),Qt::KeepAspectRatioByExpanding);

    QMetaObject::connectSlotsByName(this);
}

void TileWidget::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
    if (event->isAccepted()) return;

    selection->setPos(quantizePoint(mapToScene(event->pos()))*24);
    qDebug() << "spawn" << quantizePoint(mapToScene(event->pos()));
    QGraphicsView::mousePressEvent(event);
    Q_ASSERT(event->isAccepted());
}

void TileWidget::on_selection_movedFrom(const QPoint& point)
{
    TileMap::iterator iter = map.find(point);
    if (iter!=map.end()) map.erase(iter);
    else map.insert(point);
    qDebug() << "*****" << point << map.size() << "*****";
}

void TileWidget::drawBackground(QPainter* painter,const QRectF& clipping)
{
    qDebug() << "back";

    const int imin = std::ceil(clipping.left()/24);
    const int jmin = std::ceil(clipping.top()/24);
    const int imax = std::ceil(clipping.right()/24);
    const int jmax = std::ceil(clipping.bottom()/24);
    //qDebug() << imin << imax << jmin << jmax;
    qDebug() << sceneRect();


    painter->save();
    painter->setPen(QPen(Qt::blue,0.5));
    painter->setBrush(QBrush(painter->pen().color()));
    painter->translate(imin*24,0);
    for (int ii=imin; ii<imax; ii++) {
	painter->save();
	if (ii%5==0) painter->setPen(QPen(painter->pen().color(),painter->pen().widthF()*2));
	painter->drawLine(QPointF(0,clipping.top()),QPointF(0,clipping.bottom()));
	painter->restore();
	painter->drawText(2,10,QString("%1").arg(ii));
	painter->translate(24,0);
    }
    painter->restore();

    painter->save();
    painter->setPen(QPen(Qt::red,0.5));
    painter->setBrush(QBrush(painter->pen().color()));
    painter->translate(0,jmin*24);
    for (int jj=jmin; jj<jmax; jj++) {
	painter->save();
	if (jj%5==0) painter->setPen(QPen(painter->pen().color(),painter->pen().widthF()*2));
	painter->drawLine(QPointF(clipping.left(),0),QPointF(clipping.right(),0));
	painter->restore();
	painter->drawText(2,10,QString("%1").arg(jj));
	painter->translate(0,24);
    }
    painter->restore();

    painter->save();
    painter->setPen(QPen(Qt::green,0.5));
    painter->setBrush(QBrush(painter->pen().color()));
    foreach (const QPoint& point, map) {
	painter->drawRect(rectForPosition(point));
    }
    painter->restore();
}

