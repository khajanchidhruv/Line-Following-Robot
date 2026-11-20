#include <Arduino.h>
/* 
 * ESP32 Line Follower - Standard 30-Pin / 38-Pin Compatibility
 */

// --- Motor Control Pins ---
const int ENA = 25; // PWM Left
const int IN1 = 27; 
const int IN2 = 14; 

const int IN3 = 12; 
const int IN4 = 13; 
const int ENB = 26; // PWM Right

// --- IR Sensor Pins ---
const int SENSOR_LEFT   = 34; // Read-only input pin
const int SENSOR_MIDDLE = 35; // Read-only input pin
const int SENSOR_RIGHT  = 32; // Standard GPIO input

const int BASE_SPEED = 180; 
const int SWIFT_TURN = 220; 
const int BLACK_LINE = 1; 

int lastDirection = 0; 

void moveForward(int speedLeft, int speedRight) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedLeft);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedRight);
}

// Your proposed spinLeft (Inverted)
void spinLeft(int speed) {
  digitalWrite(IN1, HIGH);  // Left Motor FORWARD
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);   // Right Motor BACKWARD
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

// Your proposed spinRight (Inverted)
void spinRight(int speed) {
  digitalWrite(IN1, LOW);   // Left Motor BACKWARD
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);  // Right Motor FORWARD
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Note: GPIO 34 and 35 are hardware input-only pins (no pinMode output possible)
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_MIDDLE, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);

  stopMotors();
  delay(1000); 
}

void loop() {
  int left   = digitalRead(SENSOR_LEFT);
  int middle = digitalRead(SENSOR_MIDDLE);
  int right  = digitalRead(SENSOR_RIGHT);

  // Debug output to check if sensors are reading properly
  Serial.print("L: "); Serial.print(left);
  Serial.print(" | M: "); Serial.print(middle);
  Serial.print(" | R: "); Serial.println(right);

  // 1. Straight
  if (left != BLACK_LINE && middle == BLACK_LINE && right != BLACK_LINE) {
    moveForward(BASE_SPEED, BASE_SPEED);
    lastDirection = 0;
  }
  // 2. Turn Left (Single or Double sensor match)
  else if ((left == BLACK_LINE && middle == BLACK_LINE && right != BLACK_LINE) || 
           (left == BLACK_LINE && middle != BLACK_LINE && right != BLACK_LINE)) {
    spinLeft(SWIFT_TURN);
    lastDirection = -1;
  }
  // 3. Turn Right (Single or Double sensor match)
  else if ((left != BLACK_LINE && middle == BLACK_LINE && right == BLACK_LINE) || 
           (left != BLACK_LINE && middle != BLACK_LINE && right == BLACK_LINE)) {
    spinRight(SWIFT_TURN);
    lastDirection = 1;
  }
  // 4. Intersection / Cross Line
  else if (left == BLACK_LINE && middle == BLACK_LINE && right == BLACK_LINE) {
    moveForward(BASE_SPEED, BASE_SPEED);
  }
  // 5. Lost Line Recovery
  else if (left != BLACK_LINE && middle != BLACK_LINE && right != BLACK_LINE) {
    if (lastDirection == -1) {
      spinLeft(SWIFT_TURN);
    } else if (lastDirection == 1) {
      spinRight(SWIFT_TURN);
    } else {
      moveForward(BASE_SPEED, BASE_SPEED);
    }
  }

  delay(10);
}

