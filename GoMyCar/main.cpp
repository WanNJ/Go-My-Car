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

    // 640 X 480
    double frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);			// The width of frames of the video.
    double frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);		// The height of frames of the video.
    clog << "Frame Size: " << frameWidth << " X " << frameHeight << endl;

    // Initialize the used image mat and line vector.
    Mat originalImage;
    Mat roiImage;
    Mat processedImage;
    vector<NormalLine> lines;

    // Set the ROI for the image to be the bottom 1/3 of the image.
    Rect roi(0, 2*originalImage.rows/3, originalImage.rows, originalImage.cols/3);
    // Initialize the preprocessing class.
    PreProcessing process(CANNY_LOWER_BOUND, CANNY_UPPER_BOUND, CANNY_KERNEL_SIZE, HOUGH_THRESHOLD);

    while(true) {
        capture >> originalImage;
        if(originalImage.empty())
            break;

        // Get ROI.
        roiImage = originalImage(roi);
        process.allInOnce(roiImage, processedImage, lines);

        #ifdef _DEBUG
        // Get the original image.
        Rect origin(0, 0, static_cast<int>(frameWidth), static_cast<int>(frameHeight));
        Mat imgRaw = originalImage(origin);
        imshow(ORIGINAL_WINDOW_NAME, imgRaw);
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