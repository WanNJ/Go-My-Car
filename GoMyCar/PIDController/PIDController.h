/**
 * Created by Jack Wan on 7/3/18.
 */

#ifndef GOMYCAR_PIDCONTROLLER_H
#define GOMYCAR_PIDCONTROLLER_H


#include "../CarController/CarController.h"

class PIDController {
private:
    double Kp;
    int maxAbsTheta;
    CarController carController = CarController();

public:
    PIDController(double _Kp, int maxAbsTheta, CarController& _carController);
    void drive(int theta);
};


#endif //GOMYCAR_PIDCONTROLLER_H
