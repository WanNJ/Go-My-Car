#include <cstdlib>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "ImgProcessing/preProcessing.h"
#include "CarController/CarController.h"
#include "PIDController/PIDController.h"

// Comment this line at run-time to skip GUI rendering.
// #define _DEBUG

const string CAM_PATH="/dev/video0";
const string ORIGINAL_WINDOW_NAME="Original Image";
const string PROCESSED_WINDOW_NAME="Processed Image";

const int BLUR_SIZE = 5;
const int CANNY_LOWER_BOUND = 75;
const int CANNY_UPPER_BOUND = 150;
const int CANNY_KERNEL_SIZE = 3;
const int HOUGH_THRESHOLD = 100;

// TODO How to establish the mapping between photo and the physical world?

// Car Params
const double L = 160;
const int ANGLE_OFFSET = 0;

// Camera Params, Needs to be calibrated everytime.
const double FOCUS = 2;
const double HEIGHT = 1;

// Controller Params
const double K = 2;

int main() {
    // Change it to capture(CAM_PATH) when using RasPi.
    VideoCapture capture(CAM_PATH);
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
    // Initialize the coordinate system class.
    CoordinateSystem coordSys(HEIGHT, FOCUS, Vec2f(frameWidth/2, -frameHeight/6));
    // Initialize Car Control system.
    CarController carController(L, ANGLE_OFFSET);
    // Initialize PID Control system.
    PIDController pidController(K, 45, carController);

    double theta = 0;

    while(true) {
        capture >> originalImage;
        if(originalImage.empty())
            break;

        // Get ROI.
        roiImage = originalImage(roi);

        // TODO Check ROI origin position. It should be
        clog << roiImage.size << endl;

        process.allInOnce(roiImage, processedImage, lines);

        if(!lines.empty()) {
            theta = coordSys.getTheta(lines.at(0));
        } else {
            theta = 0;
        }

        // Translate radians to degrees.
        pidController.drive(static_cast<int>(theta * 180 / CV_PI));

        #ifdef _DEBUG
        // Print out the line
        vector<LineSegment>::iterator iter;
        for (iter = lines.begin(); iter != lines.end(); iter++) {
            line(roiImage, Point(static_cast<int>((*iter).x0), static_cast<int>((*iter).y0)),
                 Point(static_cast<int>((*iter).x1), static_cast<int>((*iter).y1)),
                 Scalar(0, 0, 255), 3, CV_AA);
        }

        // Show the image processing results.
        imshow(ORIGINAL_WINDOW_NAME, roiImage);
        imshow(PROCESSED_WINDOW_NAME, processedImage);
        #endif

        // Log theta.
        clog << "Theta: " << theta * 180 / CV_PI << endl;

        lines.clear();
        waitKey(1);
    }
    return 0;
}