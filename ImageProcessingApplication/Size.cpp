#include "Size.h"

Size::Size() : m_width(0), m_height(0) {}

Size::Size(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

unsigned int Size::width() const {
	return m_width;
}

unsigned int Size::height() const {
	return m_height;
}

void Size::setWidth(unsigned int width) {
	m_width = width;
}

void Size::setHeight(unsigned int height) {
	m_height = height;
}

bool Size::operator==(const Size& other) {
	return (m_width * m_height) == (other.m_width * other.m_height);
}

bool Size::operator<(const Size& other) {
	return (m_width * m_height) < (other.m_width * other.m_height);
}

bool Size::operator<=(const Size& other) {
	return (m_width * m_height) <= (other.m_width * other.m_height);
}

bool Size::operator>(const Size& other) {
	return (m_width * m_height) > (other.m_width * other.m_height);
}

bool Size::operator>=(const Size& other) {
	return (m_width * m_height) >= (other.m_width * other.m_height);
}

