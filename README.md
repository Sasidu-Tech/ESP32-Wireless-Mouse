🖱️ ESP32 Wireless Mouse

![ESP32 Wireless Mouse](images/ESP32%20Wireless%20Mouse%20(2).jpeg)

A simple wireless Bluetooth mouse built using an ESP32, MPU6050 motion sensor, and two push buttons.

The MPU6050 detects hand movement and controls the mouse cursor, while the two buttons provide Left Click and Right Click functions. The ESP32 communicates with the computer using Bluetooth HID, so no external USB receiver is required.

---

🚀 Features

- 🖱️ Wireless mouse control using Bluetooth
- 📡 Bluetooth HID communication
- 🎯 MPU6050-based cursor movement
- ↔️ X-axis and Y-axis cursor control
- 🎚️ Sensor dead-zone for reducing jitter
- 🌊 Basic sensor smoothing
- 👈 Left-click button
- 👉 Right-click button
- 🔌 No external Bluetooth receiver required

---

🧰 Components Required

Component| Quantity
ESP32 Development Board| 1
MPU6050| 1
Push Button| 2
Breadboard| 1
Jumper Wires| As required
USB Cable| 1

---

🔌 Circuit / Wiring

MPU6050 → ESP32

MPU6050 Pin| ESP32 Pin
VCC| 3.3V
GND| GND
SDA| GPIO 21
SCL| GPIO 22

Push Buttons

Function| ESP32 Pin| Other Terminal
Left Click| GPIO 25| GND
Right Click| GPIO 26| GND

The buttons use the ESP32's internal pull-up resistors with "INPUT_PULLUP".

---

📚 Libraries Used

Install the following libraries in Arduino IDE:

Wire
MPU6050
ESP32-BLE-Mouse

Important

This project uses the "MPU6050" library with:

#include <MPU6050.h>

Sensor data is read using:

mpu.getMotion6();

---

⚙️ How It Works

The project follows this process:

        MPU6050
           │
           │ I2C
           ▼
         ESP32
        /     \
       /       \
 Left Button   Right Button
    │              │
    ▼              ▼
Left Click      Right Click
        \        /
         \      /
       Bluetooth HID
            │
            ▼
     Computer / Laptop
            │
            ▼
      Wireless Mouse

Cursor Movement

The ESP32 reads accelerometer values from the MPU6050:

AX → X movement
AY → Y movement

The raw sensor values are converted into smaller mouse movement values using "map()".

Example:

int moveX = map((int)smoothX, -16000, 16000, -10, 10);

---

🎯 Dead Zone

Small sensor fluctuations can cause unwanted cursor movement.

A dead zone is therefore applied:

if (abs(ax) < 1200) {
    ax = 0;
}

if (abs(ay) < 1200) {
    ay = 0;
}

This helps reduce cursor jitter when the mouse is not intentionally moved.

---

🌊 Smoothing

Sensor values can be noisy, so basic smoothing is applied:

smoothX = smoothX * 0.85 + ax * 0.15;
smoothY = smoothY * 0.85 + ay * 0.15;

This makes cursor movement more stable.

---

🔘 Button Control

The buttons use:

pinMode(LEFT_BUTTON, INPUT_PULLUP);
pinMode(RIGHT_BUTTON, INPUT_PULLUP);

Because "INPUT_PULLUP" is used:

Button Released → HIGH
Button Pressed  → LOW

Left Click

mouse.click(MOUSE_LEFT);

Right Click

mouse.click(MOUSE_RIGHT);

---

💻 Arduino IDE Setup

1. Install ESP32 Board Support

Install the ESP32 board package in Arduino IDE.

2. Select Your Board

For example:

ESP32 Dev Module

3. Install Libraries

Install:

- MPU6050
- ESP32-BLE-Mouse

4. Connect the Hardware

Follow the wiring table above.

5. Upload the Code

Connect the ESP32 using USB and upload the Arduino sketch.

6. Pair with Computer

After uploading:

1. Power the ESP32.
2. Open Bluetooth settings on your computer.
3. Find the ESP32 Bluetooth mouse.
4. Pair/connect it.
5. Move the ESP32 to control the cursor.

---

🖥️ Serial Monitor

Open the Serial Monitor at:

115200 baud

Example output:

Initializing MPU6050...
MPU6050 Connected Successfully!
Bluetooth Mouse Started!

---

🧠 Concepts Learned

This project demonstrates several important embedded-system concepts:

- ESP32 GPIO
- I2C communication
- MPU6050 sensor interfacing
- Accelerometer data
- Gyroscope data
- Sensor data processing
- Dead-zone filtering
- Basic smoothing
- "map()" function
- Push-button input
- "INPUT_PULLUP"
- Bluetooth communication
- Bluetooth HID
- Human Interface Devices
- Event-based button detection

---

🔮 Future Improvements

Possible future improvements include:

- 🎯 Better cursor calibration
- 🌊 Advanced sensor filtering
- ⚡ Adjustable cursor sensitivity
- 🔋 Battery-powered version
- 🔘 Middle-click button
- 🖱️ Scroll functionality
- 💤 Automatic sleep mode
- 📊 Better motion-control algorithm
- 📦 Custom 3D-printed mouse enclosure

---

🎥 Demo

A demonstration video of the ESP32 Wireless Mouse will be added here.

Demo Video: Coming Soon

---

👨‍💻 Author

Sasidu Wishshanka

🎓 BICT Student – Rajarata University of Sri Lanka

Interests

- Networking
- Cyber Security
- IoT Development
- Robotics
- Arduino
- ESP32 / ESP8266

Current Learning

- CCNA
- Linux
- Python
- Ethical Hacking

---

📜 License

This project is licensed under the MIT License.

Copyright © 2026 Sasidu-Tech

---

⭐ If you found this project useful, consider giving the repository a star!
