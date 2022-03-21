#include "graphicsview.h"

GraphicsView::GraphicsView()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    setFrameStyle(0);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(700, 700);

    setScene(&scene);
    cvs = new Canvas;
    scene.addItem(cvs);
}


void GraphicsView::keyPressEvent(QKeyEvent *event) {

}
