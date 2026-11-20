#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  Serial.println("Checking motion sensor identity...");
  byte addresses[] = {0x68, 0x69};
  for (int i = 0; i < 2; i++) {
    byte addr = addresses[i];
    Wire.beginTransmission(addr);
    Wire.write(0x75); // WHO_AM_I
    if (Wire.endTransmission(false) != 0) {
      Serial.print("No response at 0x");
      Serial.println(addr, HEX);
      continue;
    }
    Wire.requestFrom(addr, (byte)1);
    if (Wire.available()) {
      Serial.print("Address: 0x");
      Serial.println(addr, HEX);
      Serial.print("WHO_AM_I: 0x");
      Serial.println(Wire.read(), HEX);
    } else {
      Serial.println("Cannot read WHO_AM_I");
    }
  }
}
void loop() {}
