/**
 * Created by Jack Wan on 6/28/18.
 */

#include "coordinateSystem.h"
#include <cmath>

NormalLine getNormLineFromGeneralForm(double rho, double theta) {
    NormalLine line{line.slope = - 1 / tan(theta), line.intercept = rho / sin(theta)};
    return line;
}

double cmTopx(double cm) {
    return 0;
}

void frameTransform(vector<NormalLine>& line) {
    // Make sure that the origin of the world frame is the camera.
}
