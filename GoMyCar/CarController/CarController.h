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
    double ratioLengthToVel;
    void initializeGPIO();

public:
    explicit CarController(double _L);
    void reset();
    void forwardSlowly();
    void forwardSlowlyByAngularVelocity(double angularVelocity);
};


#endif //GOMYCAR_CARCONTROLLER_H
