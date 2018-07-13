/**
 * Created by Jack Wan on 6/28/18.
 */

#include "coordinateSystem.h"


void CoordinateSystem::moveOriginFromROI2ImgCenter(LineSegment& segment){
    segment.x0 -= roiOrigin2imgOrigin[0];
    segment.y0 -= roiOrigin2imgOrigin[1];
    segment.x1 -= roiOrigin2imgOrigin[0];
    segment.y1 -= roiOrigin2imgOrigin[1];
}

/**
 * Please refer to the algorithm design to find the logic.
 * @param imageSeg
 * @param groundSeg
 */
void CoordinateSystem::transformFromImageToGroundFrame(LineSegment &imageSeg, LineSegment &groundSeg) {
    groundSeg.x0 = H * imageSeg.x0 / imageSeg.y0;
    groundSeg.y0 = H * f / imageSeg.y0;

    groundSeg.x1 = H * imageSeg.x1 / imageSeg.y1;
    groundSeg.y1 = H * f / imageSeg.y1;
}

/**
 * The result will always be in [-PI/2, PI]
 * @param lineSegment
 * @return
 */
double CoordinateSystem::getThetaFromLineSegment(LineSegment& lineSegment) {
    if(lineSegment.x0 == lineSegment.x1)
        return 0;
    else {
        double slope = (lineSegment.y1 - lineSegment.y0) / (lineSegment.x1 - lineSegment.x0);
        double alpha = atan(slope);
        if(alpha > 0)
            return CV_PI / 2 - alpha;
        else
            return - (CV_PI / 2 + alpha);
    }
}

/**
 * The result will be in [-PI/2, PI/2].
 * Negative means right to y, positive means left to y.
 * @param lineSegment
 * @return
 */
double CoordinateSystem::getTheta(LineSegment lineSegment) {
    LineSegment groundSeg{};

    moveOriginFromROI2ImgCenter(lineSegment);
    // Unable to calibrate focus and height, so ignore.
    transformFromImageToGroundFrame(lineSegment, groundSeg);
    return getThetaFromLineSegment(groundSeg) - CV_PI / 2;
}