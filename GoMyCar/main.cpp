#include <cstdlib>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "ImgProcessing/preProcessing.h"
#include "utils/coordinateSystem.h"

// Comment this line at run-time to skip GUI rendering.
#define _DEBUG

const string CAM_PATH="/dev/video0";
const string ORIGINAL_WINDOW_NAME="Original Image";
const string MIDDLE_WINDOW_NAME="Middle Image";
const string PROCESSED_WINDOW_NAME="Processed Image";

const int BLUR_SIZE = 5;
const int CANNY_LOWER_BOUND = 50;
const int CANNY_UPPER_BOUND = 150;
const int CANNY_KERNEL_SIZE = 3;
const int HOUGH_THRESHOLD = 75;

// H is the height of the camera in centimeters.
const double H = 7.5;
// f is the focus length of the camera in centimeters.
const double f = 20;

// TODO How to establish the mapping between photo and the physical world?

int main() {
    VideoCapture capture(0);
    // If this fails, try to open as a video camera, through the use of an integer param
    if (!capture.isOpened()) {
        std::cout << "no capture device :(" << endl;
        return -1;
    }

    // 640 X 480 for the course provided camera.
    auto frameWidth = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));			// The width of frames of the video.
    auto frameHeight = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));		// The height of frames of the video.
    clog << "Frame Size: " << frameWidth << " X " << frameHeight << endl;

    // Initialize the used image mat and line vector.
    Mat originalImage;
    Mat roiImage;
    Mat middleImage;
    Mat processedImage;
    vector<NormalLine> lines;

    // Set the ROI for the image to be the bottom 1/3 of the image.
    Rect roi(0, 2*frameHeight/3, frameWidth, frameHeight/3);
    // Initialize the preprocessing class.
    PreProcessing process(BLUR_SIZE, CANNY_LOWER_BOUND, CANNY_UPPER_BOUND, CANNY_KERNEL_SIZE, HOUGH_THRESHOLD);

    while(true) {
        capture >> originalImage;
        if(originalImage.empty())
            break;

        // Get ROI.
        roiImage = originalImage(roi);
        process.grayScalePlusGaussianBlur(roiImage, middleImage);
        process.getLines(middleImage, processedImage, lines);

        #ifdef _DEBUG
        // Get the original image.
        imshow(ORIGINAL_WINDOW_NAME, roiImage);
        imshow(MIDDLE_WINDOW_NAME, middleImage);
        imshow(PROCESSED_WINDOW_NAME, processedImage);

        // Print out the line
        vector<NormalLine>::iterator iter;
        for (iter=lines.begin();iter!=lines.end();iter++) {
            clog << "Line: Y = " << (*iter).slope << "X + " << (*iter).intercept << endl;
        }
        #endif

        lines.clear();
        waitKey(1);
    }
    return 0;
}