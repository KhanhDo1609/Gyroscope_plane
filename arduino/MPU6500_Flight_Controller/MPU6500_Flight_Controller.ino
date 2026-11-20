#include <Wire.h>
#include <math.h>

// MPU6500-compatible sensor. WHO_AM_I reported 0x70.
// Use the I2C scanner to confirm this address (usually 0x68).
const byte MPU = 0x68;
float roll = 0, pitch = 0;
unsigned long lastTime;

void writeRegister(byte reg, byte value) {
  Wire.beginTransmission(MPU);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

bool readSensor(int16_t &ax, int16_t &ay, int16_t &az,
                int16_t &gx, int16_t &gy, int16_t &gz) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU, (byte)14) != 14) return false;

  ax = (int16_t)((Wire.read() << 8) | Wire.read());
  ay = (int16_t)((Wire.read() << 8) | Wire.read());
  az = (int16_t)((Wire.read() << 8) | Wire.read());
  Wire.read(); // temperature high
  Wire.read(); // temperature low
  gx = (int16_t)((Wire.read() << 8) | Wire.read());
  gy = (int16_t)((Wire.read() << 8) | Wire.read());
  gz = (int16_t)((Wire.read() << 8) | Wire.read());
  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  writeRegister(0x6B, 0x00);
  delay(100);
  writeRegister(0x1B, 0x00);
  writeRegister(0x1C, 0x00);
  writeRegister(0x1A, 0x03);

  int16_t ax, ay, az, gx, gy, gz;
  if (!readSensor(ax, ay, az, gx, gy, gz)) {
    Serial.println("Sensor read failed");
    while (true) delay(100);
  }
  roll = atan2((float)ay, (float)az) * 180.0 / PI;
  pitch = atan2(-(float)ax,
                sqrt((float)ay * ay + (float)az * az)) * 180.0 / PI;
  lastTime = micros();
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  if (!readSensor(ax, ay, az, gx, gy, gz)) {
    delay(20);
    return;
  }

  unsigned long now = micros();
  float dt = (now - lastTime) / 1000000.0;
  lastTime = now;
  if (dt <= 0 || dt > 0.1) dt = 0.02;

  float accelRoll = atan2((float)ay, (float)az) * 180.0 / PI;
  float accelPitch = atan2(-(float)ax,
                           sqrt((float)ay * ay + (float)az * az)) * 180.0 / PI;
  float gyroRoll = gx / 131.0;
  float gyroPitch = gy / 131.0;
  roll = 0.98 * (roll + gyroRoll * dt) + 0.02 * accelRoll;
  pitch = 0.98 * (pitch + gyroPitch * dt) + 0.02 * accelPitch;

  // CSV for Chrome Web Serial: roll,pitch
  Serial.print(roll, 2);
  Serial.print(",");
  Serial.println(pitch, 2);
  delay(20);
}
