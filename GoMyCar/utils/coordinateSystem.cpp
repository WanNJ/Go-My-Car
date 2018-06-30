/**
 * Created by Jack Wan on 6/28/18.
 */

#include "coordinateSystem.h"


double cmTopx(double cm) {
    return 0;
}

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
    groundSeg.x0 = H * imageSeg.y0 / f;
    groundSeg.y0 = H * imageSeg.y0 / imageSeg.x0;

    groundSeg.x1 = H * imageSeg.y1 / f;
    groundSeg.y1 = H * imageSeg.y1 / imageSeg.x1;
}

/**
 * The result will always be in [0, PI]
 * @param lineSegment
 * @return
 */
double CoordinateSystem::getAtan2FromLineSegment(LineSegment& lineSegment) {
    if(lineSegment.y0 >= lineSegment.y1)
        return atan2(lineSegment.y0 - lineSegment.y1, lineSegment.x0 - lineSegment.x1);
    else
        return atan2(lineSegment.y1 - lineSegment.y0, lineSegment.x1 - lineSegment.x0);
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
    transformFromImageToGroundFrame(lineSegment, groundSeg);
    return getAtan2FromLineSegment(groundSeg) - CV_PI / 2;
}