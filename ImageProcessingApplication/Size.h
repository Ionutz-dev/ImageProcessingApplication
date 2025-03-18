#pragma once
class Size {

public:
	Size();
	Size(unsigned int width, unsigned int height);

	unsigned int width() const;
	unsigned int height() const;	

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);

	bool operator==(const Size& other);
	bool operator<(const Size& other);
	bool operator<=(const Size& other);
	bool operator>(const Size& other);
	bool operator>=(const Size& other);

private:
	unsigned int m_width;
	unsigned int m_height;
};

