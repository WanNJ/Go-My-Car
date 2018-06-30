#include <cstdlib>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "ImgProcessing/preProcessing.h"

// Comment this line at run-time to skip GUI rendering.
#define _DEBUG

const string CAM_PATH="/dev/video0";
const string ORIGINAL_WINDOW_NAME="Original Image";
const string PROCESSED_WINDOW_NAME="Processed Image";

const int BLUR_SIZE = 5;
const int CANNY_LOWER_BOUND = 75;
const int CANNY_UPPER_BOUND = 150;
const int CANNY_KERNEL_SIZE = 3;
const int HOUGH_THRESHOLD = 100;

// TODO How to establish the mapping between photo and the physical world?

int main() {
    // Change it to capture(CAM_PATH) when using RasPi.
    VideoCapture capture(0);
    // If this fails, try to open as a video camera, through the use of an integer param
    if (!capture.isOpened()) {
        std::cout << "No capture device :(" << endl;
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
    vector<LineSegment> lines;

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
        process.allInOnce(roiImage, processedImage, lines);

        #ifdef _DEBUG
        // Print out the line
        vector<LineSegment>::iterator iter;
        for (iter = lines.begin(); iter != lines.end(); iter++) {
            line(roiImage, Point((*iter).x0, (*iter).y0), Point((*iter).x1, (*iter).y1), Scalar(0,0,255), 3, CV_AA);
        }

        // Show the image processing results.
        imshow(ORIGINAL_WINDOW_NAME, roiImage);
        imshow(PROCESSED_WINDOW_NAME, processedImage);
        #endif

        lines.clear();
        waitKey(1);
//        getchar();
    }
    return 0;
}