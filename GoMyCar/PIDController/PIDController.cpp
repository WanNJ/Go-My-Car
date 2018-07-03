/**
 * Created by Jack Wan on 7/3/18.
 */

#include "PIDController.h"

PIDController::PIDController(double _Kp, int _maxAbsTheta, CarController& _carController) {
    Kp = _Kp;
    maxAbsTheta = _maxAbsTheta;
    carController = _carController;
}

void PIDController::drive(int theta) {
    auto controlledTheta = static_cast<int>(Kp * theta);
    if(controlledTheta < -maxAbsTheta)
        carController.forwardSlowlyWithAngle(-maxAbsTheta);
    else if(controlledTheta > maxAbsTheta)
        carController.forwardSlowlyWithAngle(maxAbsTheta);
    else
        carController.forwardSlowlyWithAngle(controlledTheta);
}
