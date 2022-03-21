#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "canvas.h"


class GraphicsView : public QGraphicsView
{
public:
    GraphicsView();

    Canvas* getCanvas() { return cvs; }


    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene scene;
    Canvas* cvs;
};

#endif // GRAPHICSVIEW_H
