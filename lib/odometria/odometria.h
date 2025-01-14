#ifndef _ODOMETRIA_H
#define _ODOMETRIA_H

#include "MPU6050.h"
#include "mbed.h"

typedef struct{
    double speed_sum;
    size_t count;
}Speed;

static double graus_to_rad(double graus);
static void graus3_to_rad3(double *graus);


class odometria{
    public:
    odometria(PinName SDA, PinName SCL);
    double read_gyro();
    double distance_read();

    private:
    MPU6050 _MPU;
    Timer time;
    Speed speed;
    double distance;//rad
    double gyro[3];
    double tolerance;

};


#endif