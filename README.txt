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