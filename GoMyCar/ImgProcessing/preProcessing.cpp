/**
 * Created by Jack Wan on 6/28/18.
 */

#include "preProcessing.h"
#include <opencv2/imgproc.hpp>

bool PreProcessing::isLineHorizontal(double x0, double y0, double x1, double y1) {
    if(x0 == x1)
        return false;

    double slope = y1 - y0 / x1 - x0;
    return -0.1 < slope && slope < 0.1;
}

PreProcessing::PreProcessing() {
    blurSize = 3;
    cannyLowerBound = 50;
    cannyUpperBound = 200;
    cannyKernelSize = 3;
    houghThreshold = 150;
};

PreProcessing::PreProcessing(int _blurSize, int cannyLower, int cannyUpper, int cannyKernel, int _houghThreshold) {
    blurSize = _blurSize;
    cannyLowerBound = cannyLower;
    cannyUpperBound = cannyUpper;
    cannyKernelSize = cannyKernel;
    houghThreshold = _houghThreshold;
}

void PreProcessing::grayScalePlusGaussianBlur(Mat& src, Mat& dst) {
    Mat middle;
    cvtColor(src, middle, cv::COLOR_RGB2GRAY);
    blur(middle, dst, Size(blurSize, blurSize));
}

void PreProcessing::getLineSegments(Mat &src, Mat &dst, vector<LineSegment> &lines){
    vector<Vec4i> detectedLines;
    Canny(src, dst, cannyLowerBound, cannyUpperBound, cannyKernelSize);

    /**
     * 1: The resolution of the parameter rho in pixels - using 1 pixel.
     * CV_PI/180: The resolution of the parameter theta in radians - using 1 degree.
     * houghThreshold: The minimum number of intersections to “detect” a line.
     */
    HoughLinesP(dst, detectedLines, 1, CV_PI/180, houghThreshold, 100, 20);
    for(vector<Vec4i>::const_iterator it = detectedLines.begin(); it != detectedLines.end(); it++) {
        // First element is distance rho, second element is angle theta.
        if(!isLineHorizontal(static_cast<double>((*it)[0]), static_cast<double>((*it)[1]), static_cast<double>((*it)[2]), static_cast<double>((*it)[3]))) {
            lines.push_back(LineSegment{static_cast<double>((*it)[0]),
                                        static_cast<double>((*it)[1]),
                                        static_cast<double>((*it)[2]),
                                        static_cast<double>((*it)[3])});
        }
    }
}

void PreProcessing::allInOnce(Mat& src, Mat& dst, vector<LineSegment>& lines) {
    grayScalePlusGaussianBlur(src, dst);
    getLineSegments(src, dst, lines);
}
