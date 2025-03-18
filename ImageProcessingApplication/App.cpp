#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Image.h"
#include "BrightnessContrastAdjustment.h"
#include "GammaCorrection.h"
#include "ImageConvolution.h"
#include "DrawingFunctions.h"
#include <iostream>
#include <iomanip>

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Image image;

	if (!image.load("dragon.ascii.pgm")) {
		std::cout << "Loading the image failed!";
	}
	else {
		int option = 0;
		
		do {
			std::cout << "\nImage Processing Menu\n";
			std::cout << "1. Apply Brightness and Contrast Adjustment\n";
			std::cout << "2. Apply Gamma Correction\n";
			std::cout << "3. Apply Mean Blur\n";
			std::cout << "4. Apply Gaussian Blur\n";
			std::cout << "5. Apply Horizontal Sobel\n";
			std::cout << "6. Apply Vertical Sobel\n";
			std::cout << "7. Draw circle\n";
			std::cout << "8. Draw line\n";
			std::cout << "9. Draw rectangle\n";
			std::cout << "0. Exit\n";
			std::cout << "Enter your option: ";
			std::cin >> option;

            switch (option) {
            case 1: {
                double alpha, beta;
                std::cout << "Enter alpha (contrast): ";
                std::cin >> alpha;
                std::cout << "Enter beta (brightness): ";
                std::cin >> beta;

                BrightnessContrastAdjustment bcAdjustment(alpha, beta);
                bcAdjustment.process(image, image);
                break;
            }
            case 2: {
                double gamma;
                std::cout << "Enter gamma value: ";
                std::cin >> gamma;

                GammaCorrection gammaCorrection(gamma);
                gammaCorrection.process(image, image);
                break;
            }
            case 3: {
                int meanBlurKernel[3][3] = {
                    {1, 1, 1},
                    {1, 1, 1},
                    {1, 1, 1}
                };
                int* meanBlurKernelPtrs[3] = { meanBlurKernel[0], meanBlurKernel[1], meanBlurKernel[2] };
                ImageConvolution meanBlurConvolution(meanBlurKernelPtrs, 3, 3, [](double val) -> double { return val / 9; });
                meanBlurConvolution.process(image, image);
                break;
            }
            case 4: {
                int gaussianKernel[3][3] = {
                    {1, 2, 1},
                    {2, 4, 2},
                    {1, 2, 1}
                };
                int* gaussianKernelPtrs[3] = { gaussianKernel[0], gaussianKernel[1], gaussianKernel[2] };
                ImageConvolution gaussianBlurConvolution(gaussianKernelPtrs, 3, 3, [](double val) -> double { return val / 16; });
                gaussianBlurConvolution.process(image, image);
                break;
            }
            case 5: {
                int sobelHorizontalKernel[3][3] = {
                    {-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}
                };
                int* sobelHorizontalKernelPtrs[3] = { sobelHorizontalKernel[0], sobelHorizontalKernel[1], sobelHorizontalKernel[2] };
                ImageConvolution sobelHorizontalConvolution(sobelHorizontalKernelPtrs, 3, 3, [](double val) -> double { return std::min(std::max(std::abs(val) / 2.0, 0.0), 255.0); });
                sobelHorizontalConvolution.process(image, image);
                break;
            }
            case 6: {
                int sobelVerticalKernel[3][3] = {
                    {-1, -2, -1},
                    { 0,  0,  0},
                    { 1,  2,  1}
                };
                int* sobelVerticalKernelPtrs[3] = { sobelVerticalKernel[0], sobelVerticalKernel[1], sobelVerticalKernel[2] };
                ImageConvolution sobelVerticalConvolution(sobelVerticalKernelPtrs, 3, 3, [](double val) -> double { return std::min(std::max(std::abs(val) / 2.0, 0.0), 255.0); });
                sobelVerticalConvolution.process(image, image);
                break;
            }
            case 7: {
                int x, y, radius;
                unsigned char color;

                std::cout << "Center (x y): ";
                std::cin >> x >> y;

                std::cout << "Radius: ";
                std::cin >> radius;

                std::cout << "Color (0-255): ";
                std::cin >> color;

                Point center(x, y);
                drawCircle(image, center, radius, color);
                break;
            }
            case 8: {
                int x1, y1, x2, y2;
                unsigned char color;

                std::cout << "Start point (x1 y1): ";
                std::cin >> x1 >> y1;

                std::cout << "End point (x2 y2): ";
                std::cin >> x2 >> y2;

                std::cout << "Color (0-255): ";
                std::cin >> color;

                Point p1(x1, y1), p2(x2, y2);
                drawLine(image, p1, p2, color);
                break;
            }
            case 9: {
                int x, y, width, height;
                unsigned char color;

                std::cout << "Top-left corner (x y): ";
                std::cin >> x >> y;

                std::cout << "Width and Height: ";
                std::cin >> width >> height;

                std::cout << "Color (0-255): ";
                std::cin >> color;

                Rectangle rect(x, y, width, height);
                drawRectangle(image, rect, color);
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option. Please enter a number between 0 and 4.\n";
            }
        } while (option != 0);

        image.save("dragon1.ascii.pgm");
	}

    _CrtDumpMemoryLeaks();

	return 0;
}