#ifndef ICM_20948_tiltcomp_H
#define ICM_20948_tiltcomp_H

#include <Arduino.h>
#include "ICM_20948.h"

extern ICM_20948_I2C imu;

void setup();
void loop();

// Returns a heading (in degrees) given an acceleration vector a due to gravity, a magnetic vector m, and a facing vector p.
// applies magnetic declination
int get_heading(float acc[3], float mag[3], float p[3], float magdec);
// subtract offsets and correction matrix to accel and mag data

void get_scaled_IMU(float Axyz[3], float Mxyz[3]) ;
// basic vector operations
void vector_cross(float a[3], float b[3], float out[3]);
float vector_dot(float a[3], float b[3]);
void vector_normalize(float a[3]);
#endif // ICM_20948_tiltcomp_H
