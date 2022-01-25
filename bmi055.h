
//  Mahasvin Gogi v0.1
//  24/01/22

#ifndef BMI055_H
#define BMI055_H

//Libraries
#include "Arduino.h"
#include <Wire.h>

// BMA250 I2C address is 0x18(24)
#define BMI_ACC_ADDR  0x18

// BMG160 I2C address is 0x68(104)
#define BMI_GYRO_ADDR  0x68

// Range Settings
#define GYRO_RANGE        0x80
#define ACCEL_RANGE        0x03

// Range Register Addresses
#define RANGE_REG    0x0F
// Bandwidth Register Addresses
#define BAND_REG    0x10

// 7.81 Hz
#define BAND_1 0x08
// 200hZ
#define BAND_2 0x04

// Registers For Data
#define DATA_REG_1 0x02 //accel
#define DATA_REG_2 0x03 //gyro

//Cannot use BMI055 as class name. Arduino error.
class BMI055_1 {

  public:

    float ax, ay, az, gx, gy, gz;

    static void Accel_init() {

      // Start I2C Transmission
      Wire.beginTransmission(BMI_ACC_ADDR);
      // Select range selection register
      Wire.write(RANGE_REG);
      // Set range +/- 2g
      Wire.write(ACCEL_RANGE);
      // Stop I2C Transmission
      Wire.endTransmission();

      // Start I2C Transmission
      Wire.beginTransmission(BMI_ACC_ADDR);
      // Select bandwidth register
      Wire.write(BAND_REG);
      // Set bandwidth 7.81 Hz
      Wire.write(BAND_1);
      // Stop I2C Transmission
      Wire.endTransmission();
      delay(300);

    }

    static void Gyro_init() {

      // Start I2C Transmission
      Wire.beginTransmission(BMI_GYRO_ADDR);
      // Select Range register
      Wire.write(RANGE_REG);
      // Configure full scale range 2000 dps
      Wire.write(GYRO_RANGE);
      // Stop I2C Transmission
      Wire.endTransmission();

      // Start I2C Transmission
      Wire.beginTransmission(BMI_GYRO_ADDR);
      // Select Bandwidth register
      Wire.write(BAND_REG);
      // Set bandwidth = 200 Hz
      Wire.write(BAND_2);
      // Stop I2C Transmission
      Wire.endTransmission();
      delay(300);
    }

    static float pollAccelerometer(float xAccl, float yAccl, float zAccl) {

      unsigned int data[0];
      // Start I2C Transmission
      Wire.beginTransmission(BMI_ACC_ADDR );
      // Select Data Registers (0x02 − 0x07)
      Wire.write(DATA_REG_1);
      // Stop I2C Transmission
      Wire.endTransmission();

      // Request 6 bytes
      Wire.requestFrom(BMI_ACC_ADDR , 6);

      // Read the six bytes
      // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
      if (Wire.available() == 6)
      {
        data[0] = Wire.read();
        data[1] = Wire.read();
        data[2] = Wire.read();
        data[3] = Wire.read();
        data[4] = Wire.read();
        data[5] = Wire.read();
      }
      delay(300);

      // Convert the data to 10 bits
      xAccl = ((data[1] * 256.0) + (data[0] & 0xC0)) / 64;
      if (xAccl > 511)
      {
        xAccl -= 1024;
      }
      yAccl = ((data[3] * 256.0) + (data[2] & 0xC0)) / 64;
      if (yAccl > 511)
      {
        yAccl -= 1024;
      }
      zAccl = ((data[5] * 256.0) + (data[4] & 0xC0)) / 64;
      if (zAccl > 511)
      {
        zAccl -= 1024;
      }

      // Output data to the serial monitor
      Serial.print("Acceleration:(LSB/g) ");
      Serial.print("\r\n");
      Serial.print("X-Axis: ");
      Serial.println(xAccl);
      Serial.print("Y-Axis: ");
      Serial.println(yAccl);
      Serial.print("Z-Axis:  ");
      Serial.println(zAccl) ;
      Serial.print("\r\n");
      Serial.print("-----------------------");
      Serial.print("\r\n");

      return (xAccl, yAccl, zAccl);
    }


    static float pollGyroscope(float xGyro, float yGyro, float zGyro) {

      unsigned int data[6];
      // Start I2C Transmission
      Wire.beginTransmission(BMI_GYRO_ADDR );
      // Select Gyrometer data register
      Wire.write(DATA_REG_2);
      // Stop I2C Transmission
      Wire.endTransmission();

      // Request 6 bytes of data
      Wire.requestFrom(BMI_GYRO_ADDR , 6);
      // Read 6 bytes of data
      // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
      if (Wire.available() == 6)
      {
        data[0] = Wire.read();
        data[1] = Wire.read();
        data[2] = Wire.read();
        data[3] = Wire.read();
        data[4] = Wire.read();
        data[5] = Wire.read();
      }
      delay(300);

      // Convert the data
      xGyro = ((data[1] * 256) + data[0]);
      yGyro = ((data[3] * 256) + data[2]);
      zGyro = ((data[5] * 256) + data[4]);

      // Output data to the serial monitor
      //(least significant bit per 9.8m/s^2)
      Serial.print("Rotation: (LSB/g)");
      Serial.print("\r\n");
      Serial.print("X-Axis: ");
      Serial.println(xGyro);
      Serial.print("Y-Axis: ");
      Serial.println(yGyro);
      Serial.print("Z-Axis: ");
      Serial.println(zGyro);
      Serial.print("\r\n");
      Serial.print("-----------------------");
      Serial.print("\r\n");
      delay(500);

      return (xGyro, yGyro, zGyro);

    }

};

#endif
