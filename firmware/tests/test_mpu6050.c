#include <assert.h>
#include <stdio.h>
#include "mpu6050.h"

int main(void) {
    mpu6050_t dev;
    assert(MPU6050_Init(&dev) == BUS_OK);
    assert(dev.who_am_i == 0x68);

    int16_t raw;
    assert(MPU6050_ReadAccelX(&dev, &raw) == BUS_OK);
    assert(raw == 0x0040); // 64

    float g = MPU6050_AccelRawToG(raw);
    assert(g > 0.0039f && g < 0.0040f);

    printf("test_mpu6050: PASS\n");
    return 0;
}