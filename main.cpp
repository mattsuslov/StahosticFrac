#include "widget.h"
#include "graphicsview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphicsView w;
    w.show();
    return a.exec();
}
