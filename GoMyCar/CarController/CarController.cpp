/**
 * Created by Jack Wan on 6/30/18.
 */

#include "CarController.h"

void CarController::initializeGPIO() {
    init();
    reset();
}

CarController::CarController() {
    L = 160;
    angleOffset = 0;
}

CarController::CarController(double _L, int _angleOffset) {
    // In mm.
    L = _L;
    angleOffset = _angleOffset;
    initializeGPIO();
}

void CarController::reset() {
    turnTo(angleOffset);
    resetCounter();
}

/**
 * Negative means left, positive means right.
 * @param angle
 */
void CarController::forwardSlowlyWithAngle(int angle) {
    controlLeft(FORWARD, 5);
    controlRight(FORWARD, 5);
    turnTo(angle + angleOffset);
}


