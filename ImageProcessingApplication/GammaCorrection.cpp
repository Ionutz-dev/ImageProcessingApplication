#include "GammaCorrection.h"
#include <cmath> 
#include <algorithm> 

GammaCorrection::GammaCorrection(double gamma) : gamma(gamma) {}

void GammaCorrection::process(const Image& src, Image& dst) {
    if (dst.width() != src.width() || dst.height() != src.height()) {
        dst = Image::zeros(src.width(), src.height());
    }

    for (unsigned int y = 0; y < src.height(); y++) {
        for (unsigned int x = 0; x < src.width(); x++) {
            unsigned char srcPixel = src.at(x, y);

            double normalizedSrcPixel = srcPixel / 255.0; 
            double correctedValue = 255.0 * std::pow(normalizedSrcPixel, 1.0 / gamma); 

            dst.at(x, y) = (unsigned char)(std::min(std::max(correctedValue, 0.0), 255.0));
        }
    }
}
