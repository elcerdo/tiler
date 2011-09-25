#include "tilewidget.h"

#include <QGraphicsRectItem>
#include <QDebug>
#include <cmath>

TileWidget::TileWidget(QWidget* parent)
    : QGraphicsView(parent), scene(NULL)
{
    scene = new QGraphicsScene(this);
    {
	static QPen pen;
	pen.setColor(Qt::black);
	pen.setWidthF(2);

	static QBrush brush;
	brush.setColor(Qt::yellow);
	brush.setStyle(Qt::Dense5Pattern);

	QGraphicsRectItem* selection = scene->addRect(0,0,24,24);
	selection->setPen(pen);
	selection->setBrush(brush);
    }

    setScene(scene);
    fitInView(QRectF(0,0,240,240),Qt::KeepAspectRatioByExpanding);
}

void TileWidget::drawBackground(QPainter* painter,const QRectF& clipping)
{
    qDebug() << "back";

    const int imin = std::ceil(clipping.left()/24);
    const int jmin = std::ceil(clipping.top()/24);
    const int imax = std::ceil(clipping.right()/24);
    const int jmax = std::ceil(clipping.bottom()/24);
    //qDebug() << imin << imax << jmin << jmax;

    painter->save();

    for (int ii=imin; ii<imax; ii++)
	painter->drawLine(QPointF(ii*24,clipping.top()),QPointF(ii*24,clipping.bottom()));
    for (int jj=jmin; jj<imax; jj++)
	painter->drawLine(QPointF(clipping.left(),jj*24),QPointF(clipping.right(),jj*24));

    painter->drawRect(clipping);
    painter->restore();
}

