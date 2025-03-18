#include "ImageConvolution.h"
#include <algorithm> 

ImageConvolution::ImageConvolution(int** kernel, int kernelW, int kernelH, ScalingFunctionPtr scalingFunc)
    : kernelWidth(kernelW), kernelHeight(kernelH), scalingFunction(scalingFunc), kernel(nullptr) {
    copyKernel(kernel, kernelW, kernelH);
}

ImageConvolution::ImageConvolution(const ImageConvolution& other)
    : kernelWidth(other.kernelWidth), kernelHeight(other.kernelHeight), scalingFunction(other.scalingFunction), kernel(nullptr) {
    copyKernel(other.kernel, other.kernelWidth, other.kernelHeight);
}

ImageConvolution& ImageConvolution::operator=(const ImageConvolution& other) {
    if (this != &other) {
        freeKernel();
        kernelWidth = other.kernelWidth;
        kernelHeight = other.kernelHeight;
        scalingFunction = other.scalingFunction;
        copyKernel(other.kernel, other.kernelWidth, other.kernelHeight);
    }
    return *this;
}

ImageConvolution::~ImageConvolution() {
    freeKernel();
}

void ImageConvolution::process(const Image& src, Image& dst) {
    if (dst.width() != src.width() || dst.height() != src.height()) {
        dst = Image::zeros(src.width(), src.height());
    }

    int srcWidth = src.width();
    int srcHeight = src.height();

    int kX = kernelWidth / 2;
    int kY = kernelHeight / 2;

    for (int y = 0; y < srcHeight; y++) {
        for (int x = 0; x < srcWidth; x++) {
            double acc = 0.0;
            for (int u = 0; u < kernelHeight; u++) {
                for (int v = 0; v < kernelWidth; v++) {
                    int pX = x - kX + v;
                    int pY = y - kY + u;
                    if (pX >= 0 && pX < srcWidth && pY >= 0 && pY < srcHeight) {
                        acc += kernel[u][v] * src.at(pX, pY);
                    }
                }
            }
            acc = scalingFunction(acc);
            acc = std::max(std::min(acc, 255.0), 0.0);
            dst.at(x, y) = (unsigned char)acc; 
        }
    }
}


void ImageConvolution::copyKernel(int** srcKernel, int width, int height) {
    kernel = new int* [height];
    for (int i = 0; i < height; i++) {
        kernel[i] = new int[width];
        for (int j = 0; j < width; j++) {
            kernel[i][j] = srcKernel[i][j];
        }
    }
}

void ImageConvolution::freeKernel() {
    if (kernel) {
        for (int i = 0; i < kernelHeight; i++) {
            delete[] kernel[i];
        }
        delete[] kernel;
        kernel = nullptr;
    }
}
