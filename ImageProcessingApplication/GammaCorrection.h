#include "ImageProcessing.h"

class GammaCorrection : public ImageProcessing {
private:
    double gamma;

public:
    GammaCorrection(double gamma);

    void process(const Image& src, Image& dst);
};

