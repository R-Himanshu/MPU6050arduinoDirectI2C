/*
 * PROJECT TITLE: MPU6050 USING WIRE.H LIBRARY 
 * DESCRIPTION: USING MPU6050 WE ARE MEASURING ALL THE 3 AXIS FOR ACCELEROEMTER, 3 AXIS OF GYROSCOPE AND TEMPERATURE.
				ALSO THIS LETS THE CODER DECIDE THE SENSITIVITY OF GYROSCOPE AND ACCELEROEMTER.
 * 
 * HARDWARE DESCRIPTION:
 * 1. ARDUINO UNO/NANO
 * 2. MPU6050
 * 
 * COMMUNICATION:
 * 1. MPU6050 - I2C PROTOCOL
 * 
 * HARDWARE CONNECTIONS:
 * 
 * ARDUINO           MPU6050         
 *   VCC              COMM             
 *   GND              COMM            
 *   D4                --               
 *   D13               --               
 *   D12               --               
 *   D11               --               
 *   A5                SCL             
 *   A4                SDA              
 *   D2                INT              
 *   D5                --  
 *-----------ACCEL SELECT------------------------------------------------------------------------------------------------------------------------- 
 *   
 *   WE CAN SELECT THE RANGE OF G TO +-2G, +-4G, +-8G AND +-16G USING THE 1C REGISTER AND ALTERING THE ACCEL_CONFIG REGISTER
 *   Wire.write(0b00000000); //Setting the accel to +/- 2g
 *   Wire.write(0b00001000); //Setting the accel to +/- 4g
 *   Wire.write(0b00010000); //Setting the accel to +/- 8g
 *   Wire.write(0b00011000); //Setting the accel to +/- 16g
 *   
 *   
 *   SO THE CALCULATION WILL BE 
 *   G_FORCE_SEL= FS/G_SEL
 *   
 *   EX: FOR +-4g
 *   
 *   G_FORCE_SEL = 32768/4 = 8192
 *   
 *   G-FORCE = accelX/G_FORCE_SEL;
 *
 *-------------GYRO SELECT------------------------------------------------------------------------------------------------------------------------
 *   WE CAN SELECT THE RANGE OF GYRO FROM +-250°/s, +-500°/s, +-1000°/s to +-2000°/s USING THE 1C REGISTER AND ALTERING THE GYRO_CONFIG REGISTER (4.4 IN THE DATASHEET)
 *   Wire.write(0b00000000); //Setting the accel to +-250°/s
 *   Wire.write(0b00001000); //Setting the accel to +-500°/s
 *   Wire.write(0b00010000); //Setting the accel to +-1000°/s
 *   Wire.write(0b00011000); //Setting the accel to +-2000°/s
 *-------------------------------------------------------------------------------------------------------------------------------------   
 *   LINK FOR THE DATASHEET: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *   
 *   DEVELOPED BY:MR. HIMANSHU RANGADHOL 
 *   PREVIOUS VERSION: VERSION V.1.0
 *   VERSION: VERSION V.1.1
 *   DATE: 28-06-2018
 *   REVISED: 15-09-2018
 *   CURRENT VERSION: 19-07-2019
 */
 
 
#include <Wire.h>

long accelX, accelY, accelZ;                      //Accelerometer raw data
float gForceX, gForceY, gForceZ;                  //Gyroscope raw data
int temp;                                         //For temperature 

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

unsigned long int milli_time;                     //variable to hold the time

void initializeMPU6050();


void setup() {
  Serial.begin(9600);
  Wire.begin();
  initializeMPU6050();
  
}


void loop() {
 
  Wire.beginTransmission(0b1101000);   //I2C address of the MPU                   //Accelerometer and Temperature reading (check 3.register map) 
  Wire.write(0x3B);                    //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,8);       //Request Accel Registers (3B - 42)
  while(Wire.available() < 8);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  temp = Wire.read()<<8| Wire.read();

  Wire.beginTransmission(0b1101000);  //I2C address of the MPU                   //Gyroscope reading (check 3.register map)
  Wire.write(0x43);                   //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);      //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ

  
  
  milli_time = millis();                                                        //Serial printing the data in CSV format
  Serial.print(milli_time);
  Serial.print(",");
  Serial.print(accelX);
  Serial.print(",");
  Serial.print(accelY);  
  Serial.print(",");
  Serial.print(accelZ);
  Serial.print(",");
  Serial.print(temp/340.00+36.53);                                           
  Serial.print(",");
  Serial.print(gyroX);
  Serial.print(",");
  Serial.print(gyroY);
  Serial.print(",");
  Serial.println(gyroZ);

  delay(250);
  
  
}

void initializeMPU6050(){
  Wire.beginTransmission(0b1101000);    //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B);                     //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000);               //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000);    //I2C address of the MPU
  Wire.write(0x1B);                     //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000);               //Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);    //I2C address of the MPU
  Wire.write(0x1C);                     //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00001000);               //Setting the accel to +/- 4g                                                                   
  Wire.endTransmission();
}
