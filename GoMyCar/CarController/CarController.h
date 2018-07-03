/**
 * Created by Jack Wan on 6/30/18.
 */

#ifndef GOMYCAR_CARCONTROLLER_H
#define GOMYCAR_CARCONTROLLER_H

#include "GPIOlib.h"

using namespace GPIO;

class CarController {
private:
    // L is the distance between the two wheels.
    double L;
    int angleOffset;
    void initializeGPIO();

public:
    explicit CarController(double _L, int _angleOffset);
    void reset();
    /**
     * @param angle in degrees
     */
    void forwardSlowlyWithAngle(int angle);
};


#endif //GOMYCAR_CARCONTROLLER_H
