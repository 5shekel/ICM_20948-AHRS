#ifndef ICM_20948_MAH
#define ICM_20948_MAH

#include <Arduino.h>
#include "ICM_20948.h"

extern ICM_20948_I2C imu;

void setup();
void loop();
void get_scaled_IMU(float Gxyz[3], float Axyz[3], float Mxyz[3]);
void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz, float deltat);
float vector_dot(float a[3], float b[3]);
void vector_normalize(float a[3]);
#endif // ICM_20948_MAH
