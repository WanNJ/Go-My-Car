/**
 * Created by Jack Wan on 6/28/18.
 */

#ifndef GOMYCAR_COORDINATESYSTEM_H
#define GOMYCAR_COORDINATESYSTEM_H

struct NormalLine {
    double slope;
    double intercept;
};

NormalLine getNormLineFromGeneralForm(double rho, double theta);

#endif //GOMYCAR_COORDINATESYSTEM_H
