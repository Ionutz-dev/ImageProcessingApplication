#include "ImageProcessing.h"

#pragma once
class BrightnessContrastAdjustment : public ImageProcessing {
	double alpha;
	double beta;
		
public:
	BrightnessContrastAdjustment();
	BrightnessContrastAdjustment(double alpha, double beta);

	void process(const Image& src, Image& dst);
};

