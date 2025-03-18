#include "Size.h"
#include "Rectangle.h"
#include <string>

#pragma once
class Image {

public:
	Image();
	Image(unsigned int width, unsigned int height);
	Image(const Image& other);
	Image& operator=(const Image& other);	
	~Image();

	bool load(std::string imagePath);
	bool save(std::string imagePath) const;

	Image operator+(const Image& image);
	Image operator-(const Image& image);
	Image operator*(double scalar);

	bool getROI(Image& roiImg, Rectangle roiRect);
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned width, unsigned int height);

	bool isEmpty() const;

	Size size() const;

	unsigned int width() const;
	unsigned int height() const;
	unsigned char& at(unsigned int x, unsigned int y);
	unsigned char& at(unsigned int x, unsigned int y) const;
	unsigned char& at(Point point);
	unsigned char* row(int y);	

	void release();

	friend std::ostream& operator<<(std::ostream& os, const Image& image);
	friend std::istream& operator>>(std::istream& is, Image& image);

	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);

	void displayPGMAsASCII();

	std::string pixelToAnsiGray(unsigned int pixel);

	void display();

private:
	unsigned char** m_data;
	unsigned int m_width;
	unsigned int m_height;
};

