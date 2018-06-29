#include <cstdlib>
#include <iostream>

#include <opencv2/highgui.hpp>

#include "ImgProcessing/preProcessing.h"
#include "utils/coordinateSystem.h"

// Comment this line at run-time to skip GUI rendering.
#define _DEBUG

const string CAM_PATH="/dev/video0";
const string ORIGINAL_WINDOW_NAME="Original Image";
const string PROCESSED_WINDOW_NAME="Processed Image";

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
    VideoCapture capture(CAM_PATH);
    // If this fails, try to open as a video camera, through the use of an integer param
    if (!capture.isOpened()) {
        capture.open(atoi(CAM_PATH.c_str()));
    }

    double frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);			// The width of frames of the video.
    double frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);		// The height of frames of the video.
    clog << "Frame Size: " << frameWidth << " x " << frameHeight << endl;

    // Initialize the used image mat and line vector.
    Mat originalImage;
    Mat processedImage;
    vector<NormalLine> lines;

    capture >> originalImage;
    // Set the ROI for the image to be the bottom 1/3 of the image.
    Rect roi(0, 2*originalImage.rows/3, originalImage.rows, originalImage.cols/3);
    // Initialize the preprocessing class.
    PreProcessing process(CANNY_LOWER_BOUND, CANNY_UPPER_BOUND, CANNY_KERNEL_SIZE, HOUGH_THRESHOLD, roi);

    while(true) {
        capture >> originalImage;
        if(originalImage.empty())
            break;

        process.allInOnce(originalImage, processedImage, lines);

        #ifdef _DEBUG
        imshow(ORIGINAL_WINDOW_NAME, originalImage);
        imshow(PROCESSED_WINDOW_NAME, processedImage);

        // Print out the line
        vector<NormalLine>::iterator iter;
        for (iter=lines.begin();iter!=lines.end();iter++) {
            clog << "Line: Y = " << (*iter).slope << "X + " << (*iter).intercept << endl;
        }
        #endif
    }

    return 0;
}