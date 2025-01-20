#ifndef _ODOMETRIA_H
#define _ODOMETRIA_H

#include "MPU6050.h"
#include "mbed.h"

#define GRAUS_TO_RAD 0.017453293F

class odometria{
    public:
    odometria(int freq_p, PinName SDA, PinName SCL);
    double read_gyro();
    void update_gyro();
    double speed_read();
    void gyro_read(double destino[]);
    double distance_read();

    private:
    MPU6050 _MPU;
    Timer time;
    Ticker intr_update_gyro;
    int freq;
    double speed = 0.0;// w speed
    double distance_total = 0.0;//rad
    double tolerance = 0.01;//rad/s
    double gyro[3] = {0.0, 0.0, 0.0}; //{x,y,w}

};


#endif