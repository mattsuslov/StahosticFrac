#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QVector2D>
#include <QVector3D>
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <random>
#include <time.h>
#include <QRandomGenerator>
#include <iostream>
#include <algorithm>

class Canvas : public QGraphicsItem
{
public:
    Canvas();

    QRectF boundingRect() const {
        return QRectF(0, 0, width_, height_);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {

    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
        gen_pixmap();
        update();
    }

private:
    int width_, height_;
    QVector2D lb_, rt_;
    QVector2D pressed_;
    QVector2D cur_;
    QPixmap pixmap_;
    bool move_ = false;

    void gen_pixmap();
    void build(int lx, int ly, int rx, int ry, std::vector<std::vector<double>>& field);
    void prebuild(std::vector<std::vector<double>>& field);
};

#endif // CANVAS_H
