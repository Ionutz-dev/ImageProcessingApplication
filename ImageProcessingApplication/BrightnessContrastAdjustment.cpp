#include "BrightnessContrastAdjustment.h"
#include "Image.h"

BrightnessContrastAdjustment::BrightnessContrastAdjustment() : alpha(1.0), beta(0.0) {}

BrightnessContrastAdjustment::BrightnessContrastAdjustment(double alpha, double beta) : alpha(alpha), beta(beta) {}

void BrightnessContrastAdjustment::process(const Image& src, Image& dst) {
    if (dst.width() != src.width() || dst.height() != src.height()) {
        dst = Image::zeros(src.width(), src.height());
    }

    for (unsigned int y = 0; y < src.height(); y++) {
        for (unsigned int x = 0; x < src.width(); x++) {
            unsigned char srcPixel = src.at(x, y);

            double processedValue = std::min(std::max(alpha * srcPixel + beta, 0.0), 255.0);

            dst.at(x, y) = (unsigned char)processedValue; 
        }
    }
}
