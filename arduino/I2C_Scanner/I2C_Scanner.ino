#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  Serial.println("Scanning I2C...");
}
void loop() {
  int devices = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) Serial.print('0');
      Serial.println(address, HEX);
      devices++;
    }
  }
  if (devices == 0) Serial.println("No I2C devices found");
  delay(2000);
}
