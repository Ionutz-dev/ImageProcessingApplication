#include "Rectangle.h"
#include <algorithm>

Rectangle::Rectangle() : m_x(0), m_y(0), m_width(0), m_height(0) {};

Rectangle::Rectangle(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {};

int Rectangle::x() const {
	return m_x;
}

int Rectangle::y() const {
	return m_y;
}

int Rectangle::width() const {
	return m_width;
}

int Rectangle::height() const {
	return m_height;
}

void Rectangle::setX(int x) {
	m_x = x;
}

void Rectangle::setY(int y) {
	m_y = y;
}

void Rectangle::setWidth(int width) {
	m_width = width;
}

void Rectangle::setHeight(int height) {
	m_height = height;
}

Rectangle Rectangle::operator+(const Point& point) {
	return Rectangle(m_x + point.x(), m_y + point.y(), m_width, m_height);
}

Rectangle Rectangle::operator-(const Point& point) {
	return Rectangle(m_x + point.x(), m_y + point.y(), m_width, m_height);
}

Rectangle Rectangle::operator&(const Rectangle& other) {
    int xStart = std::max(m_x, other.m_x);
    int yStart = std::max(m_y, other.m_y);
    int xEnd = std::min(m_x + m_width, other.m_x + other.m_width);
    int yEnd = std::min(m_y + m_height, other.m_y + other.m_height);

    if (xStart < xEnd && yStart < yEnd) 
        return Rectangle(xStart, yStart, xEnd - xStart, yEnd - yStart);

    return Rectangle();
}

Rectangle Rectangle::operator|(const Rectangle& other) {
    int xStart = std::min(m_x, other.m_x);
    int yStart = std::min(m_y, other.m_y);
    int xEnd = std::max(m_x + m_width, other.m_x + other.m_width);
    int yEnd = std::max(m_y + m_height, other.m_y + other.m_height);

    return Rectangle(xStart, yStart, xEnd - xStart, yEnd - yStart);
}




