#include "odometria.h"
#include <cmath>

odometria::odometria(int freq_p,PinName SDA, PinName SCL) : _MPU(SDA, SCL){
    freq = freq_p;

    _MPU.initialize();
    time.start();

    intr_update_gyro.attach(callback(this, &odometria::update_gyro), std::chrono::microseconds(freq));
}

static double graus_to_rad(double &graus){
    return graus * GRAUS_TO_RAD;
}

static void graus3_to_rad3(double graus[]){
    graus[0] = graus_to_rad(graus[0]);
    graus[1] = graus_to_rad(graus[1]);
    graus[2] = graus_to_rad(graus[2]);
    return;
}

double odometria::read_gyro(){
    double gyro_new_read[3];
    double gyro_diff[3];
    this->_MPU.readGyro(gyro_new_read);
    graus3_to_rad3(gyro_new_read);
    for(int i=0;i<3;i++){
        gyro_new_read[i] = roundl(gyro_new_read[i] * 100) / 100;
        gyro_diff[i] = gyro[i] - gyro_new_read[i];
    }

    if(fabs(gyro_diff[0]) >= tolerance || fabs(gyro_diff[1]) >= tolerance || gyro_diff[2] >= tolerance){// se o valor absoluto lido de cada eixo for maior que a tolerancia
        gyro[0] = gyro_new_read[0];
        gyro[1] = gyro_new_read[1];
        gyro[2] = gyro_new_read[2];
        
        speed = gyro[2];
    }
    return gyro[2];// w rad/s
}

void odometria::update_gyro(){
    read_gyro();
    distance_total += speed * (std::chrono::duration_cast<std::chrono::microseconds>(time.elapsed_time()).count());
    time.reset();//reinicia a contagem entre leituras

}

double odometria::speed_read(){
    return this->speed;
}
void odometria::gyro_read(double destino[]){
    destino[0] = gyro[0];
    destino[1] = gyro[1];
    destino[2] = gyro[2];
}
double odometria::distance_read(){
    return this->distance_total;
}