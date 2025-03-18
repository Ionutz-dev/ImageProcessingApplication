# ImageProcessingApplication

## Overview

**ImageProcessingApplication** is a C++ project built in Visual Studio for applying various image processing techniques to grayscale `.pgm` images. The application includes functions such as brightness and contrast adjustment, gamma correction, convolution filters, and custom drawing tools.

---

## Features

- 🖼️ **Image Loading**: Supports `.pgm` (Portable GrayMap) ASCII image files.
- 🎚️ **Brightness & Contrast Adjustment**: Modify pixel values to enhance image visibility.
- 🌗 **Gamma Correction**: Adjust the luminance of images using gamma transformations.
- 🌀 **Convolution Filters**: Apply filters (e.g., blur, edge detection) using kernel convolutions.
- ✏️ **Drawing Functions**: Custom functions to draw shapes (e.g., lines, rectangles) over images.

---

## Technologies Used

- **C++**
- **Visual Studio 2022+**
- **PGM File Format**
- Standard C++ libraries (no external dependencies)

---

## Project Structure

```
ImageProcessingApplication/
│
├── ImageProcessingApplication.sln              # Visual Studio solution file
│
├── ImageProcessingApplication/                 # Source code and assets
│   ├── App.cpp                                 # Main application entry point
│   ├── BrightnessContrastAdjustment.cpp/.h     # Brightness/contrast logic
│   ├── GammaCorrection.cpp/.h                  # Gamma correction logic
│   ├── Image.cpp/.h                            # Image loading and saving
│   ├── ImageConvolution.cpp/.h                 # Image convolution functions
│   ├── DrawingFunctions.h                      # Shape drawing functions
│   └── *.ascii.pgm                             # Sample grayscale images
│       ├── feep.ascii.pgm
│       ├── dragon.ascii.pgm
│       ├── glassware_noisy.ascii.pgm
│       └── ...
│
├── .vs/                                        # Visual Studio workspace files
```

---

## Setup Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/ImageProcessingApplication.git
   cd ImageProcessingApplication
   ```

2. **Open in Visual Studio**:
   - Double-click `ImageProcessingApplication.sln`.
   - Let Visual Studio load the solution and index files.

3. **Build & Run**:
   - Press `Ctrl + Shift + B` to build.
   - Press `F5` to run the application.

---

## Sample Usage

- Load an image like `feep.ascii.pgm`.
- Apply filters or adjustments using command-line prompts or function calls.
- Save or display processed images (console/text-based output).

---

## License

This project is for educational purposes and does not include a formal license. Free to use for learning or research.

