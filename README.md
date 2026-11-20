# SkyFlight — Arduino Motion-Controlled Arcade Game ✈️

3D browser airplane game (Three.js) with keyboard and Arduino Uno + MPU6500-compatible gyro/accelerometer (WHO_AM_I `0x70`).

## Contents
- `index.html`: SkyFlight V2 browser game with Web Serial `Connect Arduino`, `Calibrate` and keyboard fallback.
- `arduino/MPU6500_Flight_Controller/MPU6500_Flight_Controller.ino`: Arduino firmware sending roll/pitch CSV at 115200 baud.
- `arduino/I2C_Scanner/I2C_Scanner.ino`: I2C address scanner.
- `arduino/WHO_AM_I_Check/WHO_AM_I_Check.ino`: sensor chip identity checker.
- `docs/WIRING.md`: wiring and troubleshooting.

## Quick start
1. Connect the sensor to Arduino Uno: SDA → A4, SCL → A5, GND → GND, VCC → power supported by your exact breakout. Only use 5V if both breakout supply and I2C logic compatibility are confirmed; otherwise use 3.3V with suitable logic-level shifting.
2. Upload the `MPU6500_Flight_Controller.ino` sketch with Arduino IDE. It uses `Wire.h` only.
3. Close Arduino IDE Serial Monitor/Plotter before connecting from Chrome.
4. From the repository root run `python3 -m http.server 8000`.
5. Open Chrome at `http://localhost:8000/index.html` (not a preview iframe).
6. Click `Connect Arduino`, choose `cu.usbmodem...`, then `Calibrate` and start the game.

Keyboard controls: W/S up/down, A/D left/right, Space boost, P pause, R restart. The sensor outputs `roll,pitch` at 115200 baud. Three.js loads from a CDN, so internet is required.

## Known notes
- The connected sensor reported WHO_AM_I `0x70` and is likely MPU6500-compatible. Adafruit MPU6050 library may reject it; the included firmware reads registers directly.
- Web Serial needs desktop Chrome and the local webpage must not be embedded inside a restricted iframe.
- If port is busy, close Serial Monitor. If browser shows 404, run the server from the folder containing `index.html`.
- Hardware and browser combination have not been fully end-to-end validated.

No open-source license has been selected.
