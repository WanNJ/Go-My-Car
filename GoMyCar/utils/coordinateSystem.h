/**
 * Created by Jack Wan on 6/28/18.
 */

#ifndef GOMYCAR_COORDINATESYSTEM_H
#define GOMYCAR_COORDINATESYSTEM_H

#include <vector>

using namespace std;

struct NormalLine {
    double slope;
    double intercept;
};

NormalLine getNormLineFromGeneralForm(double rho, double theta);

void frameTransform(vector<NormalLine>& line);

double cmTopx(double cm);
#endif //GOMYCAR_COORDINATESYSTEM_H
