
//  Mahasvin Gogi v0.1
//  24/01/22

// Hook-Up Instructions
// SDA Pin 21
// SCL Pin 22


//*********CHANGE FILE PATH TO YOUR OWN!*********//

#include <C:\Users\mahas\OneDrive\Documents\Arduino\BMI055\BMI055.ino\bmi055\bmi055.h>

//**********************************************//
 
// Instantiate Object
BMI055_1  IMU;

void setup ()
{

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Initialisation Methods
  IMU.Accel_init;
  IMU.Gyro_init;

}

void loop ()
{
  // Data polling Methods
  IMU.pollAccelerometer(IMU.ax, IMU.ay, IMU.az);
  IMU.pollGyroscope(IMU.gx, IMU.gy, IMU.gz);
  delay(500);

}
