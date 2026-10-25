#include "app.h"
#include "mpu6050.h"
#include <stdio.h>

static mpu6050_t imu;

void App_Init(void) {
    if (MPU6050_Init(&imu) == BUS_OK) {
        printf("App: MPU-6050 ready (WHO=0x%02X)\n", imu.who_am_i);
    } else {
        printf("App: MPU-6050 init FAILED\n");
    }
}

void App_Loop(void) {
    int16_t raw;
    if (MPU6050_ReadAccelX(&imu, &raw) == BUS_OK) {
        printf("App: AccelX=%d (%.2f g)\r\n", raw, MPU6050_AccelRawToG(raw));
    } else {
        printf("App: MPU read FAIL\r\n");
    }
    HAL_Delay(1000);
}