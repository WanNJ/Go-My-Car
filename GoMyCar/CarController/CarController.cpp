/**
 * Created by Jack Wan on 6/30/18.
 */

#include "CarController.h"

void CarController::initializeGPIO() {
    init();
}

CarController::CarController(double _L) {
    // In mm.
    L = _L;
    ratioLengthToVel = 1;
    initializeGPIO();
}

void CarController::reset() {
    resetCounter();
}

void CarController::forwardSlowly() {
    controlLeft(FORWARD, 5);
    controlRight(FORWARD, 5);
}

void CarController::forwardSlowlyByAngularVelocity(double angularVelocity) {
    double delta_v = angularVelocity * L / ;
}


