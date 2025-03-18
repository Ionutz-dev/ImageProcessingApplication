#include "ImageProcessing.h"
#include "Image.h"

typedef double (*ScalingFunctionPtr)(double);

class ImageConvolution : public ImageProcessing {
private:
    int** kernel;
    int kernelWidth;
    int kernelHeight;
    ScalingFunctionPtr scalingFunction;

    void copyKernel(int** srcKernel, int width, int height);
    void freeKernel();

public:
    ImageConvolution(int** kernel, int kernelWidth, int kernelHeight, ScalingFunctionPtr scalingFunc);
    ImageConvolution(const ImageConvolution& other);
    virtual ~ImageConvolution();

    ImageConvolution& operator=(const ImageConvolution& other);

    void process(const Image& src, Image& dst);
};
