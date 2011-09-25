#include <QApplication>
#include "tilewidget.h"

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);

    TileWidget tile;
    tile.resize(805,805);
    tile.show();

    return app.exec();
}



