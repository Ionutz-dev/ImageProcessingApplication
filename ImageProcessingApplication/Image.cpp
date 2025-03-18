#include <fstream>
#include <iostream>
#include <iomanip>
#include "Size.h"
#include "Image.h"

Image::Image() : m_data(nullptr), m_width(0), m_height(0) {};

Image::Image(unsigned int width, unsigned int height) {
	m_width = width;
	m_height = height;

	m_data = new unsigned char*[m_height];
	for (unsigned int i = 0; i < m_height; i++) {
		m_data[i] = new unsigned char[m_width];

		for (unsigned int j = 0; j < m_width; j++)
			m_data[i][j] = static_cast < unsigned char>(0);
	}
};

Image::Image(const Image& other) {
	m_width = other.m_width;
	m_height = other.m_height;

	m_data = new unsigned char*[m_height];
	for (unsigned int i = 0; i < m_height; i++) {
		m_data[i] = new unsigned char[m_width];

		for (unsigned int j = 0; j < m_width; j++)
			m_data[i][j] = other.m_data[i][j];
	}
};

Image& Image::operator=(const Image& other) {
	if (this != &other) {
		if (m_data) {
			for (unsigned int i = 0; i < m_height; i++) 
				delete[] m_data[i];
			delete[] m_data;
		}

		m_width = other.m_width;
		m_height = other.m_height;

		m_data = new unsigned char* [m_height];
		for (unsigned int i = 0; i < m_height; i++) {
			m_data[i] = new unsigned char[m_width];

			for (unsigned int j = 0; j < m_width; j++)
				m_data[i][j] = other.m_data[i][j];
		}
	}
	return *this;
}

Image::~Image() {
	release();
};

bool Image::isEmpty() const {
	return m_data == nullptr && m_width == 0 && m_height == 0;
}

Size Image::size() const {
	return Size(m_width, m_height);
}

bool Image::load(std::string imagePath) {
	std::ifstream file(imagePath);
	if (!file) return false;

	file >> *this;
	return true;
}

bool Image::save(std::string imagePath) const {
	std::ofstream file(imagePath);
	if (!file) return false;

	file << *this;
	return true;
}

Image Image::operator+(const Image& image) {
	if (m_width != image.m_width || m_height != image.m_height) 
		throw std::exception("Images must be of the same size for addition");

	Image result(m_width, m_height);
	for (unsigned int i = 0; i < m_height; i++)
		for (unsigned int j = 0; j < m_width; j++) {
			unsigned int addition = m_data[i][j] + image.m_data[i][j];
			if (addition > 255) addition = 255;
			result.m_data[i][j] = addition;
		}

	return result;
}

Image Image::operator-(const Image& image) {
	if (m_width != image.m_width || m_height != image.m_height)
		throw std::exception("Images must be of the same size for subtraction");

	Image result(m_width, m_height);
	for (unsigned int i = 0; i < m_height; i++)
		for (unsigned int j = 0; j < m_width; j++) {
			unsigned int subtraction = m_data[i][j] - image.m_data[i][j];
			if (subtraction < 0) subtraction = 0;
			result.m_data[i][j] = subtraction;
		}

	return result;
}

Image Image::operator*(double scalar) {
	Image result(m_width, m_height);
	for (unsigned int i = 0; i < m_height; i++)
		for (unsigned int j = 0; j < m_width; j++) {
			double multiplication = scalar * m_data[i][j];
			if (multiplication > 255.0) multiplication = 255.0;	
			result.m_data[i][j] = multiplication;
		}

	return result;
}

bool Image::getROI(Image& roiImg, Rectangle roiRect) {
	return getROI(roiImg, roiRect.x(), roiRect.y(), roiRect.width(), roiRect.height());
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned width, unsigned int height) {
	if (x + width > m_width || y + height > m_height)
		return false; 

	roiImg.release();

	roiImg.m_width = width;
	roiImg.m_height = height;

	roiImg.m_data = new unsigned char* [height];
	for (unsigned int i = 0; i < height; i++) {
		roiImg.m_data[i] = new unsigned char[width];
		for (unsigned int j = 0; j < width; ++j) 
			roiImg.m_data[i][j] = m_data[y + i][x + j];
	}

	return true;
}

unsigned int Image::width() const {
	return m_width;
}

unsigned int Image::height() const {
	return m_height;	
}

unsigned char& Image::at(unsigned int x, unsigned int y) {
	if (x >= m_width || y >= m_height)
		throw std::exception("Coordinates out of bounds");
	return m_data[y][x];
}

unsigned char& Image::at(unsigned int x, unsigned int y) const {
	if (x >= m_width || y >= m_height)
		throw std::exception("Coordinates out of bounds");
	return m_data[y][x];
}

unsigned char& Image::at(Point point) {
	if (point.x() >= m_width || point.y() >= m_height)
		throw std::exception("Point out of bounds");
	return m_data[point.y()][point.x()];
}

unsigned char* Image::row(int y) {
	if (y >= m_height) {
		throw std::exception("Row out of bounds");
	}
	return m_data[y];
}

void Image::release() {
	if (m_data) {
		for (unsigned int i = 0; i < m_height; i++)
			delete[] m_data[i];
		delete[] m_data;
	}
}

std::ostream& operator<<(std::ostream& os, const Image& image) {
	os << "P2\n" << "# pgm image \n" << image.m_width << " " << image.m_height << "\n255\n";
	for (unsigned int i = 0; i < image.m_height; i++) {
		for (unsigned int j = 0; j < image.m_width; j++)
			os << static_cast<unsigned int>(image.m_data[i][j]) << " ";
		os << "\n";
	}
	return os;
}

std::istream& operator>>(std::istream& is, Image& image) {
	std::string line;
	std::getline(is, line); 
	std::getline(is, line);

	is >> image.m_width >> image.m_height;

	image.release();

	image.m_data = new unsigned char* [image.m_height];
	for (unsigned int i = 0; i < image.m_height; i++) 
		image.m_data[i] = new unsigned char[image.m_width];

	unsigned char maxValue[5] = "";
	is >> maxValue; 

	for (unsigned int i = 0; i < image.m_height; i++) 
		for (unsigned int j = 0; j < image.m_width; j++) {
			unsigned int pixelValue;
			is >> pixelValue;
			image.m_data[i][j] = static_cast<unsigned char>(pixelValue);
		}

	return is;
}

Image Image::zeros(unsigned int width, unsigned int height) {
	Image image(width, height);

	for (unsigned int i = 0; i < height; i++) 
		for (unsigned int j = 0; j < width; j++)
			image.m_data[i][j] = 0;

	return image;
}

Image Image::ones(unsigned int width, unsigned int height) {
	Image image(width, height);

	for (unsigned int i = 0; i < height; i++) 
		for (unsigned int j = 0; j < width; j++)
			image.m_data[i][j] = 1;

	return image;
}



