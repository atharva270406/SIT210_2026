#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// HC-SR04 Pins
const int trigPin = 2;
const int echoPin = 3;

// Output Pins
const int ledPin = 6;
const int buzzerPin = 9;

// Light Threshold
const float DARK_THRESHOLD = 20.0;

void setup() {

  Serial.begin(9600);

  Wire.begin();
  lightMeter.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.println("Smart Blind Assistance System Started");
}

void loop() {

  // ===== Ultrasonic Sensor =====

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  float distance;

  if (duration == 0)
    distance = 999;
  else
    distance = duration * 0.0343 / 2;

  // ===== Light Sensor =====

  float lux = lightMeter.readLightLevel();

  // ===== LED Control =====

  if (lux < DARK_THRESHOLD)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);

  // ===== Buzzer Control =====

  if (distance < 15) {

    tone(buzzerPin, 2000);

  }
  else if (distance < 30) {

    tone(buzzerPin, 2000);
    delay(100);
    noTone(buzzerPin);
    delay(100);

  }
  else if (distance < 50) {

    tone(buzzerPin, 2000);
    delay(300);
    noTone(buzzerPin);
    delay(300);

  }
  else {

    noTone(buzzerPin);

  }

  // ===== Send Data To Raspberry Pi =====

  Serial.print("Distance=");
  Serial.print(distance);

  Serial.print(",Light=");
  Serial.println(lux);

  delay(500);
}
