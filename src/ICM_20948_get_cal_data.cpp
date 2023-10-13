/*
a.k.a ICM_20948_get_cal_data.ino
SENSOR CALIBRATION
Gyro, magnetometer and accelerometer calibration is required, 
for each sensor individually. The Arduino program ICM_20948_get_cal_data.ino 
collects gyro data and calculates the gyro offset (while the sensor 
is held still), then collects 300 accelerometer and magnetometer data 
points, while the user slowly and carefully rotates the sensor in 3D.
*/

#include <Arduino.h>
#include "helpers.h" // Include the helper functions to print the data nicely
#include "ICM_20948.h" // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU


#define WIRE_PORT Wire // Your desired Wire port.
#define AD0_VAL 1      // The value of the last bit of the I2C address.                \
  // On the SparkFun 9DoF IMU breakout the default is 1, and when \
  // the ADR jumper is closed the value becomes 0

ICM_20948_I2C myICM; // Otherwise create an ICM_20948_I2C object

// gyro offset values for calibration
long gyro[3] = {0};
int offset_count = 500; //average this many values for gyro
int acc_mag_count = 300; //collect this many values for acc/mag calibration

void setup()
{

  SERIAL_PORT.begin(115200);
  while (!SERIAL_PORT)
  {
  };


  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);


  //myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  bool initialized = false;
  while (!initialized)
  {


    myICM.begin(WIRE_PORT, AD0_VAL);

    SERIAL_PORT.print(F("Initialization of the sensor returned: "));
    SERIAL_PORT.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      SERIAL_PORT.println("Trying again...");
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }
  // find gyro offsets
  SERIAL_PORT.println(F("Hold sensor still for gyro offset calibration ..."));
  delay(5000);

  float goff;
  int i;

  for (i = 0; i < offset_count; i++) {
    if (myICM.dataReady())
    {
      myICM.getAGMT();         // The values are only updated when you call 'getAGMT'
      gyro[0] += myICM.agmt.gyr.axes.x;
      gyro[1] += myICM.agmt.gyr.axes.y;
      gyro[2] += myICM.agmt.gyr.axes.z;
    }
  } //done with gyro
  SERIAL_PORT.print("Gyro offsets x, y, z: ");
  for (i = 0; i < 3; i++) {
    goff = (float)gyro[i] / offset_count;
    SERIAL_PORT.print(goff, 1);
    SERIAL_PORT.print(", ");
  }
  SERIAL_PORT.println();

  SERIAL_PORT.println(F("Turn sensor SLOWLY and STEADILY in all directions until done"));
  delay(5000);
  SERIAL_PORT.println(F("Starting..."));

  // get values for calibration of acc/mag
  for (i = 0; i < acc_mag_count; i++) {
    if (myICM.dataReady())
    {
      myICM.getAGMT();         // The values are only updated when you call 'getAGMT'
      printRawAGMT( myICM.agmt );     // raw values, taken directly from the agmt structure
      delay(200);
    }
    else
    {
      delay(100); //wait for data ready
    }
  }
  SERIAL_PORT.print(F("Done collecting"));
}

void loop() {}
