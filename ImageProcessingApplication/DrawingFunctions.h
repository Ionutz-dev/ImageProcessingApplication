#include "Image.h"
#include <cmath> 

inline void drawCircle(Image& img, Point center, int radius, unsigned char color) {
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        img.at(center.x() + x, center.y() + y) = color;
        img.at(center.x() + y, center.y() + x) = color;
        img.at(center.x() - y, center.y() + x) = color;
        img.at(center.x() - x, center.y() + y) = color;
        img.at(center.x() - x, center.y() - y) = color;
        img.at(center.x() - y, center.y() - x) = color;
        img.at(center.x() + y, center.y() - x) = color;
        img.at(center.x() + x, center.y() - y) = color;
        y++;

        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        }
        else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}

inline void drawLine(Image& img, Point p1, Point p2, unsigned char color) {
    int dx = std::abs(p2.x() - p1.x()), sx = p1.x() < p2.x() ? 1 : -1;
    int dy = -std::abs(p2.y() - p1.y()), sy = p1.y() < p2.y() ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        img.at(p1.x(), p1.y()) = color;
        if (p1.x() == p2.x() && p1.y() == p2.y()) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy; 
            p1.setX(p1.x() + sx); 
        }
        if (e2 <= dx) {
            err += dx;
            p1.setY(p1.y() + sy); 
        }
    }
}


inline void drawRectangle(Image& img, Rectangle r, unsigned char color) {
    Point tl(r.x(), r.y());
    Point br(r.x() + r.width(), r.y() + r.height());
    drawLine(img, tl, Point(br.x(), tl.y()), color);
    drawLine(img, Point(br.x(), tl.y()), br, color);
    drawLine(img, br, Point(tl.x(), br.y()), color);
    drawLine(img, Point(tl.x(), br.y()), tl, color);
}
