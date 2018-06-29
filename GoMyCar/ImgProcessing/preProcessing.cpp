/**
 * Created by Jack Wan on 6/28/18.
 */

#include "preProcessing.h"
#include <opencv2/imgproc.hpp>


PreProcessing::PreProcessing() {
    cannyLowerBound = 50;
    cannyUpperBound = 150;
    cannyKernelSize = 3;
    houghThreshold = 50;
};

PreProcessing::PreProcessing(int cannyLower, int cannyUpper, int cannyKernel, int _houghThreshold) {
    cannyLowerBound = cannyLower;
    cannyUpperBound = cannyUpper;
    cannyKernelSize = cannyKernel;
    houghThreshold = _houghThreshold;
}

void PreProcessing::grayScalePlusGaussianBlur(Mat& src, Mat& dst) {
    cvtColor(src, dst, cv::COLOR_RGB2GRAY);
    blur(src, dst, Size(3,3) );
}

void PreProcessing::getLines(Mat& src, Mat& dst, vector<NormalLine>& lines) {
    vector<Vec2f> detectedLines;

    Canny(dst, dst, cannyLowerBound, cannyUpperBound, cannyKernelSize);
    /**
     * 1: The resolution of the parameter rho in pixels - using 1 pixel.
     * CV_PI/180: The resolution of the parameter theta in radians - using 1 degree.
     * houghThreshold: The minimum number of intersections to “detect” a line.
     */
    HoughLines(dst, detectedLines, 1, CV_PI/180, houghThreshold);
    for(vector<Vec2f>::const_iterator it = detectedLines.begin(); it != detectedLines.end(); it++) {
        // First element is distance rho, second element is angle theta.
        lines.push_back(getNormLineFromGeneralForm((*it)[0], (*it)[1]));
    }
}

void PreProcessing::allInOnce(Mat& src, Mat& dst, vector<NormalLine>& lines) {
    grayScalePlusGaussianBlur(src, dst);
    getLines(src, dst, lines);
}
