/**
 * Created by Jack Wan on 6/28/18.
 */

#include "coordinateSystem.h"
#include <cmath>

NormalLine getNormLineFromGeneralForm(double rho, double theta) {
    NormalLine line{line.slope = - 1 / tan(theta), line.intercept = rho / sin(theta)};
    return line;
}