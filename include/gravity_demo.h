#ifndef GRAVITY_DEMO_H
#define GRAVITY_DEMO_H

#include <Arduino.h>
#include "ICM_20948.h"

extern ICM_20948_I2C imu;

void setup();
void loop();
void get_scaled_IMU(float Gxyz[], float Axyz[], float Mxyz[]);
void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz, float deltat);

#endif // GRAVITY_DEMO_H
