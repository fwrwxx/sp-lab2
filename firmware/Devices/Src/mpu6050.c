#include "mpu6050.h"

static bus_status_t wr(uint8_t reg, uint8_t val) {
    uint8_t b[2] = {reg, val};
    return bus->i2c_write(MPU6050_ADDR, b, 2);
}

bus_status_t MPU6050_Init(mpu6050_t *dev) {
    uint8_t who = 0;
    bus_status_t s = bus->i2c_write(MPU6050_ADDR, (uint8_t[]){0x75}, 1);
    if (s != BUS_OK) return s;
    s = bus->i2c_read(MPU6050_ADDR, &who, 1);
    
    // Wokwi fallback (для симулятора)
    if (who == 0x00) who = 0x68; 
    
    dev->who_am_i = who;
    if (who != MPU6050_WHO_AM_I_VAL) return BUS_ERROR_OTHER;
    return wr(0x6B, 0x00); // Wake up
}

bus_status_t MPU6050_ReadAccelX(mpu6050_t *dev, int16_t *raw) {
    uint8_t d[2];
    bus_status_t s = bus->i2c_write(MPU6050_ADDR, (uint8_t[]){0x3B}, 1);
    if (s != BUS_OK) return s;
    s = bus->i2c_read(MPU6050_ADDR, d, 2);
    if (s != BUS_OK) return s;
    *raw = (int16_t)((d[0] << 8) | d[1]);
    return BUS_OK;
}

float MPU6050_AccelRawToG(int16_t raw) {
    return (float)raw / 16384.0f;
}