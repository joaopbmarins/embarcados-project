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
    }

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
