#include "canvas.h"
Canvas::Canvas()
{
    width_ = 1000, height_ = 700;
    rt_ = {2, 2};
    lb_ = {-2, -1};
    gen_pixmap();
    update();
}


std::mt19937 rnd();

QRandomGenerator rd(time(0));
int range = 500;
double rcolor(int max_range=256, double power=2) {
    return std::pow(rd.generateDouble(), power) * max_range - max_range / 2;
}

void bound(double& v) {
    v = std::max(0., v);
    v = std::min(255., v);
}

void Canvas::build(int lx, int ly, int rx, int ry, std::vector<std::vector<double>>& field) {
    if (rx - lx <= 1 && ry - ly <= 1) return;
    int my = ly + (ry - ly) / 2, mx = lx + (rx - lx) / 2;


    double scale = std::min((rx - lx) * 1.0 / height_, (ry - ly) * 1.0 / width_);
    if (field[mx][my] == -1) {
        field[mx][my] = (field[lx][ry] + field[rx][ry] + field[lx][ly] + field[rx][ly]) / 4;
        field[mx][my] += rcolor(range) * scale;
        bound(field[mx][my]);
    }
    if (field[lx][my] == -1) {
        field[lx][my] = (field[mx][my] + field[lx][ly] + field[lx][ry]) / 3;
        field[lx][my] += rcolor(range) * scale;
        bound(field[lx][my]);
    }
    if (field[rx][my] == -1) {
        field[rx][my] = (field[mx][my] + field[rx][ly] + field[rx][ry]) / 3;
        field[rx][my] += rcolor(range) * scale;
        bound(field[rx][my]);
    }
    if (field[mx][ly] == -1) {
        field[mx][ly] = (field[mx][my] + field[lx][ly] + field[rx][ly]) / 3;
        field[mx][ly] += rcolor(range) * scale;
        bound(field[mx][ly]);
    }
    if (field[mx][ry] == -1) {
        field[mx][ry] = (field[mx][my] + field[lx][ry] + field[rx][ry]) / 3;
        field[mx][ry] += rcolor(range) * scale;
        bound(field[mx][ry]);
    }


    build(lx, ly, mx, my, field);
    build(mx, my, rx, ry, field);
    build(mx, ly, rx, my, field);
    build(lx, my, mx, ry, field);
}

void Canvas::prebuild(std::vector<std::vector<double>>& field) {
    field.assign(height_, std::vector<double>(width_, -1));
    field[0][0] = 0;
    field[height_ - 1][0] = 255;
    field[0][width_-1] = 0;
    field[height_ - 1][width_-1] = 255;
}

void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(0, 0, width_, height_, pixmap_);
}

QColor gen_color(double h, double depth) {
    depth = 1 - depth;
    if (h < 0.02) {
        return QColor(0, 0, 255 * depth);
    } else if (h < 0.6) {
        return QColor(256 * pow(1 - h, 10) * depth, 100 * depth, 0);
    } else {
        depth *= 255;
        return QColor(depth, depth, depth);
    }
}


void Canvas::gen_pixmap() {
    pixmap_ = QPixmap(width_, height_);
    QPainter painter(&pixmap_);
    painter.setBrush(Qt::cyan);
    painter.drawRect(0, 0, width_, height_);
    std::vector<std::vector<double>> red, blue, green;

    range = 5;
    prebuild(blue);
    build(0, 0, height_ - 1, width_ - 1, blue);

    for (int i = height_ - 1; i >= 0; --i) {
        for (int j = 0; j < width_; ++j) {
            painter.setPen(QColor(blue[i][j], blue[i][j] / 4, blue[i][j] / 2));
            painter.drawPoint(j, i);
        }
    }

    range = 400;
    prebuild(red);
    build(0, 0, height_ - 1, width_ - 1, red);

    QMatrix m;
    m.translate(0, height_ + 100);
    m.scale(1, -1);

    painter.setTransform(QTransform(m));

    for (int i = height_ - 1; i >= 0; --i) {
        for (int j = 0; j < width_; ++j) {
//            QVector2D vec = QVector2D(j, i* cos(M_PI / 3) + red[i][j] * sin(M_PI / 3));

            QVector2D vec = QVector2D(j, i);
//            painter.setPen(gen_color(red[i][j] / 256, pow(i * 1.0 / height_, 2)));
            painter.drawLine(QPoint(j, 0), vec.toPoint());
            painter.setPen(gen_color(red[i][j] / 256, pow(i * 1.0 / height_, 2)));
//            painter.setPen(gen_color(red[i][j] / 256, pow(i * 1.0 / height_, 2)));
            painter.drawPoint(vec.toPoint());
        }
    }
}
