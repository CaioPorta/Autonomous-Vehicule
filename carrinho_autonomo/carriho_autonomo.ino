// Autonomous Car Obstacle Avoidance
#include <Servo.h>

// ==================== PIN DEFINITIONS ====================
#define TRIG1_PIN  4
#define ECHO1_PIN  7
#define TRIG2_PIN  5
#define ECHO2_PIN  8
#define TRIG3_PIN  6
#define ECHO3_PIN  9

#define LED_LEFT_PIN  2
#define LED_RIGHT_PIN 10
#define MOTOR_PIN     13
#define BUZZER_PIN    3
#define SERVO_PIN     11

// ==================== CONFIGURATION ====================
#define BLINK_DURATION_MS   60
#define CRITICAL_DISTANCE   40  // K1 - immediate avoidance
#define WARNING_DISTANCE    60  // K2 - partial turn
#define CENTER_ANGLE        90

Servo servo;

// ==================== SENSOR READING ====================
long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration / 2 / 29.1;
}

// ==================== LED INDICATOR ====================
void blinkIndicator(int ledPin, int buzzerPin, int blinkCount, int blinkDuration) {
  for (int i = 0; i < blinkCount; i++) {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(blinkDuration);
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(blinkDuration);
  }
}

// ==================== SETUP ====================
void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.println("STARTING...");

  pinMode(TRIG1_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
  pinMode(TRIG2_PIN, OUTPUT);
  pinMode(ECHO2_PIN, INPUT);
  pinMode(TRIG3_PIN, OUTPUT);
  pinMode(ECHO3_PIN, INPUT);

  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);

  digitalWrite(LED_LEFT_PIN, HIGH);
  digitalWrite(LED_RIGHT_PIN, HIGH);
  digitalWrite(MOTOR_PIN, HIGH);

  servo.attach(SERVO_PIN);
  servo.write(CENTER_ANGLE);
  delay(500);
}

// ==================== MAIN LOOP ====================
void loop() {
  long distFront = readDistance(TRIG1_PIN, ECHO1_PIN);
  long distLeft  = readDistance(TRIG2_PIN, ECHO2_PIN);
  long distRight = readDistance(TRIG3_PIN, ECHO3_PIN);

  // Debug output
  // Serial.print("distance1: ");
  // Serial.println(distFront);
  // Serial.print("distance2: ");
  // Serial.println(distLeft);
  // Serial.print("distance3: ");
  // Serial.println(distRight);
  // delay(50);

  int servoAngle = CENTER_ANGLE;
  bool obstacleDetected = false;

  // Critical zone: immediate full turn
  if (distFront < CRITICAL_DISTANCE || distLeft < CRITICAL_DISTANCE || distRight < CRITICAL_DISTANCE) {
    obstacleDetected = true;

    if (distFront < distLeft && distFront < distRight) {
      blinkIndicator(LED_LEFT_PIN, BUZZER_PIN, 2, BLINK_DURATION_MS);
      servoAngle = 50;  // full left
    }
    else if (distRight < distFront && distRight < distLeft) {
      blinkIndicator(LED_RIGHT_PIN, BUZZER_PIN, 2, BLINK_DURATION_MS);
      servoAngle = 130;  // full right
    }
  }
  // Warning zone: partial turn
  else if (distFront < WARNING_DISTANCE || distLeft < WARNING_DISTANCE || distRight < WARNING_DISTANCE) {
    obstacleDetected = true;

    if (distFront < distLeft && distFront < distRight) {
      blinkIndicator(LED_LEFT_PIN, BUZZER_PIN, 2, BLINK_DURATION_MS);
      servoAngle = 70;  // partial left
    }
    else if (distRight < distFront && distRight < distLeft) {
      blinkIndicator(LED_RIGHT_PIN, BUZZER_PIN, 2, BLINK_DURATION_MS);
      servoAngle = 110;  // partial right
    }
  }

  servo.write(servoAngle);
  delay(15);

  if (!obstacleDetected) {
    servo.write(CENTER_ANGLE);
  }
}
