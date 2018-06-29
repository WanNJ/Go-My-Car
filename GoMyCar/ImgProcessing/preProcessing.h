/**
 * Created by Jack Wan on 6/28/18.
 */

#ifndef GOMYCAR_PREPROCESSING_H
#define GOMYCAR_PREPROCESSING_H

#include <vector>
#include <cv.h>
#include "../utils/coordinateSystem.h"

using namespace cv;
using namespace std;

class PreProcessing {
private:
    Rect roi;
    int cannyLowerBound;
    int cannyUpperBound;
    int cannyKernelSize;
    int houghThreshold;

public:
    /**
    * Default values.
    * ROI is default to the whole image.
    */
    PreProcessing();

    /**
    * Canny recommended a upper:lower ratio between 2:1 and 3:1.
    * @param cannyLower
    * @param cannyUpper
    * @param cannyKernel The Kernel Size.
    * @param _houghThreshold How many points is needed at least to identify a line.
    * @param _roi
    */
    PreProcessing(int cannyLower, int cannyUpper, int cannyKernel, int _houghThreshold, Rect _roi);

    void setROI(Rect rect);
    /**
     * Get the Region of Interests.
     * @param src source image mat.
     * @param dst the dst image mat.
     */
    void getROI(Mat& src, Mat& dst);
    /**
     * Transform the image to gray scale and then apply Gaussian blur to it.
     * The params are all set in the constructor.
     */
    void grayScalePlusGaussianBlur(Mat& src, Mat& dst);
    /**
    * First apply canny edge detector to it.
    * @param src
    * @param dst The result of canny edge detector will be written into it.
    * @param lanes
    */
    void getLines(Mat& src, Mat& dst, vector<NormalLine>& lines);
};

#endif //GOMYCAR_PREPROCESSING_H
