#ifndef __TILEWIDGET_H__
#define __TILEWIDGET_H__

#include <QGraphicsScene>
#include <QGraphicsView>

class TileWidget : public QGraphicsView {
    Q_OBJECT
    public:
	TileWidget(QWidget* parent=NULL);
    protected:
	void drawBackground(QPainter* painter,const QRectF& clipping);
	QGraphicsScene* scene;
};

#endif

