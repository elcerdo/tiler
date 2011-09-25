#include "tilewidget.h"

#include <QGraphicsRectItem>
#include <QDebug>
#include <cmath>

TileWidget::TileWidget(QWidget* parent)
    : QGraphicsView(parent), scene(NULL)
{
    selection = new SelectionItem(this);

    scene = new QGraphicsScene(this);
    scene->addItem(selection);

    setDragMode(QGraphicsView::NoDrag);
    setScene(scene);

    setSceneRect(QRectF(0,0,24,24));
    scale(2,2);
    //fitInView(QRectF(0,0,240,240),Qt::KeepAspectRatioByExpanding);
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

}

