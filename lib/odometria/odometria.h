#ifndef _ODOMETRIA_H
#define _ODOMETRIA_H

#include "MPU6050.h"
#include "mbed.h"

typedef struct{
    double speed_sum;
    size_t count;
}Speed;

static double graus_to_rad(double &graus);
static void graus3_to_rad3(double graus[]);


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