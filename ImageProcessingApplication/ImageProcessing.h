#include "Image.h"

#pragma once
class ImageProcessing {

public:
	virtual void process(const Image& src, Image& dst) = 0;
};

