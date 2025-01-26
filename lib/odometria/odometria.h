#ifndef _ODOMETRIA_H
#define _ODOMETRIA_H

#include "MPU6050.h"
#include "mbed.h"

/*
Resultado da operação PI/180
*/
#define GRAUS_TO_RAD 0.017453293F

class odometria{
    public:
    /*
    @param freq_p tempo em milisegundos entre cada leitura
    @param SDA Pinos onde está conectado o MPU6050
    @param SCL Pinos onde está conectado o MPU6050
    */
    odometria(int freq_p, PinName SDA, PinName SCL);
    /*
    Atualiza os valores da classe de velocidade e distância
    */
    void update_gyro();
    /*
    Retorna a velocidade
    */
    double speed_read();
    /*
    Recebe um vetor de três posições e altera os valores dele para os valores lidos pelo giroscopio
    @param destino[3] vetor que receberá os valores lidos
    */
    void gyro_read(double destino[]);
    /*
    Retorna a distância acumulada
    */
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
    double read_gyro();

};


#endif