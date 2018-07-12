/**
 * Created by Jack Wan on 6/28/18.
 */

#ifndef GOMYCAR_COORDINATESYSTEM_H
#define GOMYCAR_COORDINATESYSTEM_H

#include <vector>
#include <cv.h>

using namespace std;
using namespace cv;

struct LineSegment {
    double x0;
    double y0;
    double x1;
    double y1;
};

class CoordinateSystem {
private:
    // H is the height of the camera in centimeters.
    double H;
    // f is the focus length of the camera in centimeters.
    double f;
    Vec2f roiOrigin2imgOrigin;

    void moveOriginFromROI2ImgCenter(LineSegment& segment);
    void transformFromImageToGroundFrame(LineSegment& imageSeg, LineSegment& groundSeg);
    double getAtan2FromLineSegment(LineSegment& lineSegment);
public:
    CoordinateSystem(const double _H, const double _f, const Vec2f _roiOrigin2imgOrigin) {
        H = _H;
        f = _f;
        roiOrigin2imgOrigin = _roiOrigin2imgOrigin;
    }

    double getTheta(LineSegment lineSegment);
};

#endif //GOMYCAR_COORDINATESYSTEM_H
