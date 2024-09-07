#include <Wire.h>

// MPU6050 Registers
#define MPU             0x68   // I2C address
#define PWR_MGMT_1      0x6B   
#define GYRO_XOUT_H     0x43   
#define GYRO_YOUT_H     0x45   
#define GYRO_ZOUT_H     0x47   
#define GYRO_SENSITIVITY  131.0 

// store gyroscope data
int16_t gyroX, gyroY, gyroZ;
float yaw = 0.0;
float previousTime, currentTime, elapsedTime;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Initialize MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(PWR_MGMT_1);  
  Wire.write(0);           
  Wire.endTransmission(true);

  previousTime = millis(); // Initialize time
}

void loop() {
  // Read gyroscope data
  Wire.beginTransmission(MPU);
  Wire.write(GYRO_XOUT_H); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

 
  gyroX = Wire.read() << 8 | Wire.read(); 
  gyroY = Wire.read() << 8 | Wire.read(); 
  gyroZ = Wire.read() << 8 | Wire.read(); 

  // Calculate elapsed time
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0; // Convert to seconds
  previousTime = currentTime;

  // Convert gyroscope data to degrees per second
  float gyroZrate = (float)gyroZ / GYRO_SENSITIVITY;

  // Calculate the yaw angle 
  yaw += gyroZrate * elapsedTime;

  // Print the yaw value to the Serial Monitor
  Serial.print("Yaw: ");
  Serial.println(yaw);
  
  delay(1000);  // Delay to control data output rate (adjust as needed)
}
