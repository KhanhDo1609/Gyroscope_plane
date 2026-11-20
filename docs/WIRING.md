# Wiring: Arduino Uno R3 + MPU6500-compatible sensor

Disconnect power before modifying connections.

| Sensor pin | Arduino Uno R3 pin |
| --- | --- |
| VCC | 5V *only if breakout supports 5V power and 5V I2C logic* |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

The MPU6500 chip itself is a 3.3V part. Some breakout boards support 5V VCC through an onboard regulator, but 5V I2C signal compatibility is **not guaranteed**. For a 3.3V-only board, use an appropriate 3.3V supply and bidirectional I2C logic-level shifter. Confirm your actual breakout board specifications.

No connection required for XDA, XCL, INT, or AD0 when using the standard address.

## Troubleshooting

- **No I2C devices found:** Check source voltage, GND, SDA/A4, SCL/A5, pin solder joints, and connector contact.
- **WHO_AM_I = 0x70:** Consistent with an MPU6500. The Adafruit MPU6050 library can reject it. Use the included direct-register sketch.
- **Arduino address is 0x69:** Change `const byte MPU = 0x68;` to `const byte MPU = 0x69;` in the flight-controller sketch.
- **Serial output:** The controller emits CSV `roll,pitch` once every ~20 ms at `115200 baud`, for example `0.42,-0.18`.
- **Chrome can't connect:** Close Arduino IDE Serial Monitor/Plotter, open the game in desktop Chrome at `http://localhost:8000/index.html` rather than a preview iframe.
