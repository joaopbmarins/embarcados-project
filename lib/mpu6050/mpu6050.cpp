#include "mpu6050.h"
#include <string>

/*
I2c Class
Note: The Arm Mbed API uses 8 bit addresses, so make sure to left-shift 7 bit addresses by 1 bit before passing them. 
*/

MPU6050::MPU6050(PinName SDA, PinName SCL) : i2c(SDA, SCL){//inicia o i2c
    i2c.frequency(400000); // configura o i2c para o modo rapido 400kHz (modo lento 100kHz)

    if(this->read_single_byte(WHO_AM_I_REG) != MPU6050_I2C_ADDRESS){
        fprintf(stderr, "erro ao conectar com o mpu6050\n");
        return;
    }

    this->power_reg1_config(0, 0, 0, 0, INT_8MHz_OSC);//acorda, sem sleep, sem cycle, sensor de temp ligado, clock interno 8mhz

    this->gyro_reg_config(GYRO_ST_OFF, GFS_2000dps);//gyro no alcance maximo
    this->accel_reg_config(ACC_ST_OFF, AFS_16g);//accel no alcance maximo

    return;
}

char MPU6050::read_single_byte(char addr){
    char addr_reg_read = addr;
    char slave_addr = MPU6050_I2C_ADDRESS << 1;
    char valor_reg = 0;

    this->i2c.write(slave_addr && 0xFE, &addr_reg_read, 1);
    this->i2c.read(slave_addr || 0x01, &valor_reg, 1);

    return valor_reg;
}

int MPU6050::write_single_byte(char addr, char value){
    char slave_addr = MPU6050_I2C_ADDRESS << 1;
    char addr_reg_write = addr;
    int ack=1;

    ack = this->i2c.write(slave_addr && 0xFE, &addr_reg_write, 1);
    if(ack == 0){
        ack = this->i2c.write(slave_addr && 0xFE, &value, 1);
    }
    return ack;// se ack for = 0, escrita recebida, se for != 0 erro na escrita
}

void MPU6050::read_mult_bytes(char addr, char *vet, size_t size){
    char addr_reg_read = addr;
    char slave_addr = MPU6050_I2C_ADDRESS << 1;

    //if(vet == nullptr) return;

    this->i2c.write(slave_addr && 0xFE, &addr_reg_read, 1);
    this->i2c.read(slave_addr || 0x01, vet, size);

    return;
}

int MPU6050::write_mult_bytes(char addr, char *vet, size_t size){
    char slave_addr = MPU6050_I2C_ADDRESS << 1;
    char addr_reg_write = addr;
    int ack=1;

    ack = this->i2c.write(slave_addr && 0xFE, &addr_reg_write, 1);
    if(ack == 0){
        ack = this->i2c.write(slave_addr && 0xFE, vet, size);
    }
    return ack;// se ack for = 0, escrita recebida, se for != 0 erro na escrita
}

void MPU6050::power_reg1_config(int dev_res, int sleep, int cycle, int temp_dis, int clk_sel){
    char data = 0;

    data = data | (dev_res << 7);
    data = data | (sleep << 6);
    data = data | (cycle << 5);
    data = data | (temp_dis << 3);
    data = data | (dev_res);

    this->write_single_byte(PWR_MGMT_1_REG, data);
}

void MPU6050::power_reg2_config(int LP_WAKE, int STB_XA, int STB_YA, int STB_ZA, int STB_XG, int STB_YG, int STB_ZG){
    char data = 0;

    data = data | (LP_WAKE << 6);
    data = data | (STB_XA << 5);
    data = data | (STB_YA << 4);
    data = data | (STB_ZA << 3);
    data = data | (STB_XG << 2);
    data = data | (STB_YG << 1);
    data = data | (STB_ZA << 0);

    this->write_single_byte(PWR_MGMT_2_REG, data);

}

void MPU6050::gyro_reg_config(int self_test, int full_scale){
    char data = 0;

    data = data | (self_test << 5);
    data = data | (full_scale << 3);

    this->write_single_byte(GYRO_CONFIG_REG, data);
}

void MPU6050::accel_reg_config(int self_test, int full_scale){
    char data = 0;

    data = data | (self_test << 5);
    data = data | (full_scale << 3);

    this->write_single_byte(ACCEL_CONFIG_REG, data);
}



