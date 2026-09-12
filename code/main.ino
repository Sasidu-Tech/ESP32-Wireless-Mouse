#include <Wire.h>
#include <MPU6050.h>
#include <BleMouse.h>

MPU6050 mpu;
BleMouse mouse;

// Button pins
const int LEFT_BUTTON = 25;
const int RIGHT_BUTTON = 26;

// Previous button states
bool lastLeftState = HIGH;
bool lastRightState = HIGH;

float smoothX = 0;
float smoothY = 0;

void setup() {

  Serial.begin(115200);

  // MPU6050
  Wire.begin(21, 22);

  Serial.println("Initializing MPU6050...");

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected Successfully!");
  } 
  else {
    Serial.println("MPU6050 Connection Failed!");
  }

  // Buttons
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  // Bluetooth Mouse
  mouse.begin();

  Serial.println("Bluetooth Mouse Started!");
}

void loop() {

  // =========================
  // MPU6050 DATA
  // =========================

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);


  // =========================
  // DEAD ZONE
  // =========================

  if (abs(ax) < 1200) {
    ax = 0;
  }

  if (abs(ay) < 1200) {
    ay = 0;
  }


  // =========================
  // SMOOTHING
  // =========================

  smoothX = smoothX * 0.85 + ax * 0.15;
  smoothY = smoothY * 0.85 + ay * 0.15;


  // =========================
  // CURSOR MOVEMENT
  // =========================

  int moveX = map((int)smoothY, -16000, 16000, 10, -10);
  int moveY = map((int)smoothX, -16000, 16000, -10, 10);


  if (mouse.isConnected()) {

    if (moveX != 0 || moveY != 0) {
      mouse.move(moveX, moveY);
    }
  }


  // =========================
  // LEFT BUTTON
  // =========================

  bool leftState = digitalRead(LEFT_BUTTON);

  if (lastLeftState == HIGH && leftState == LOW) {

    if (mouse.isConnected()) {
      mouse.click(MOUSE_LEFT);
    }

    Serial.println("LEFT CLICK");
  }


  // =========================
  // RIGHT BUTTON
  // =========================

  bool rightState = digitalRead(RIGHT_BUTTON);

  if (lastRightState == HIGH && rightState == LOW) {

    if (mouse.isConnected()) {
      mouse.click(MOUSE_RIGHT);
    }

    Serial.println("RIGHT CLICK");
  }


  // Save current button states
  lastLeftState = leftState;
  lastRightState = rightState;


  delay(10);
}
