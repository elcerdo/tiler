#include <QApplication>
#include "tilewidget.h"

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);

    TileWidget tile;
    tile.resize(800,800);
    tile.show();

    return app.exec();
}



