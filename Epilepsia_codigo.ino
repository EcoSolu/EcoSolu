#include <TinyWireM.h>
// #define DEBUG 1  // - uncomment this line to display accel/gyro values
#ifdef DEBUG
#endif

int accelX, accelY, accelZ;
int gyroX, gyroY, gyroZ;
int gyroXold, gyroYold, gyroZold;
char mpu = 0x68;  // I2C address of MPU.  Connect 5V to pin ADO to use 0x69 address instead


void setup() {
  
  TinyWireM.begin();
  // We need to do three things.  1. Disable sleep mode on the MPU (it activates on powerup).  2. Set the scale of the Gyro.  3. Set the scale of the accelerometer
  // We do this by sending 2 bytes for each:  Register Address & Value
  TinyWireM.beginTransmission(mpu); 
  TinyWireM.write(0x6B); //  Power setting address
  TinyWireM.write(0b00000000); // Disable sleep mode (just in case)
  TinyWireM.endTransmission();
  TinyWireM.beginTransmission(mpu); 
  TinyWireM.write(0x1B); // Config register for Gyro
  TinyWireM.write(0x00000000); // 250° per second range (default)
  TinyWireM.endTransmission();
  TinyWireM.beginTransmission(mpu); //I2C address of the MPU
  TinyWireM.write(0x1C); // Accelerometer config register
  TinyWireM.write(0b00000000); // 2g range +/- (default)
  TinyWireM.endTransmission();
}

void loop() {
  getAccel();
  getGyro();
  if (shaken()) {
    //variables accelX; accelY; accelZ    
    #endif
  }
  if (stirred()) {
    //variables gyroX; gyroY; gyroZ
    #endif
  }
  }

void getAccel() {
  TinyWireM.beginTransmission(mpu); //I2C address of the MPU
  TinyWireM.write(0x3B); //  Acceleration data register
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(mpu, 6); // Get 6 bytes, 2 for each DoF
  accelX = TinyWireM.read() LTLT 8; // Get X upper byte first
  accelX |= TinyWireM.read();     // lower
  accelY = TinyWireM.read() LTLT 8; // Get Y upper byte first
  accelY |= TinyWireM.read();     // lower
  accelZ = TinyWireM.read() LTLT 8; // Get Z upper byte first
  accelZ |= TinyWireM.read();     // lower
}

void getGyro() {
  TinyWireM.beginTransmission(mpu); //I2C address of the MPU
  TinyWireM.write(0x43); // Gyro data register
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(mpu, 6); // Get 6 bytes, 2 for each DoF
  while (TinyWireM.available() LT 6);
  gyroX = TinyWireM.read() LTLT 8; // Get X upper byte first
  gyroX |= TinyWireM.read();     // lower
  gyroY = TinyWireM.read() LTLT 8; // Get Y upper byte first
  gyroY |= TinyWireM.read();     // lower
  gyroZ = TinyWireM.read() LTLT 8; // Get Z upper byte first
  gyroZ |= TinyWireM.read();     // lower
}

bool shaken() {
  if ((abs(accelX) GT 20000) || (abs(accelY) GT 20000) ||  (abs(accelZ) GT 32760)) {
  return true;
  }
  else return false;
  }

bool stirred() {
  gyroXold = gyroX;    // Save current Gyro settings...
  gyroYold = gyroY;
  gyroZold = gyroZ;
  getGyro();  // get a second reading to compare with the last to see if we're moving
  //  300 is just a number to filter noise-level fluxuations .. DYOR
  if (((gyroX - gyroXold) GT 300) || ((gyroY - gyroYold) GT 300) ||  ((gyroZ - gyroZold) GT 300)) {


    
    return true;
  }
  else return false;
}
