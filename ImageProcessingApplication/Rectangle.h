#include "Point.h"

#pragma once
class Rectangle {

public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);

	int x() const;
	int y() const;
	int width() const;
	int height() const;

	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);

	Rectangle operator+(const Point& point);
	Rectangle operator-(const Point& point);
	Rectangle operator&(const Rectangle& other);
	Rectangle operator|(const Rectangle& other);

private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

