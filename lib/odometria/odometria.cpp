#include "odometria.h"
#include <cmath>

odometria::odometria(PinName SDA, PinName SCL) : _MPU(SDA, SCL){
    _MPU.initialize();
    time.start();
    gyro[0] = 0.0;
    gyro[1] = 0.0;
    gyro[2] = 0.0;
    tolerance = 2000.0 * 0.03;
    speed.count = 0;
    speed.speed_sum = 0.0;
}

static double graus_to_rad(double graus){
    return graus * (M_PI/180.0);
}

static void graus3_to_rad3(double *graus){
    graus[0] = graus[0] * (M_PI/180.0);
    graus[1] = graus[1] * (M_PI/180.0);
    graus[2] = graus[2] * (M_PI/180.0);
    return;
}

double odometria::read_gyro(){
    this->_MPU.readGyro(gyro);
    if(fabs(gyro[0]) > tolerance || fabs(gyro[1]) > tolerance || gyro[2] > tolerance){// se o valor absoluto lido de cada eixo for maior que a tolerancia

    }

}