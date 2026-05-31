#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

const int PIR_PIN = 2;
const int SWITCH_PIN = 3;
const int LED1 = 5;
const int LED2 = 6;

volatile bool motionDetected = false;
volatile bool switchChanged = false;

const float DARK_THRESHOLD = 20.0;

void PIR_ISR() {
  motionDetected = true;
}

void SWITCH_ISR() {
  switchChanged = true;
}

void setup() {
  Serial.begin(9600);

  while (!Serial);

  pinMode(PIR_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  Wire.begin();
  lightMeter.begin();

  attachInterrupt(
    digitalPinToInterrupt(PIR_PIN),
    PIR_ISR,
    RISING
  );

  attachInterrupt(
    digitalPinToInterrupt(SWITCH_PIN),
    SWITCH_ISR,
    CHANGE
  );

  Serial.println("Linda Smart Lighting System Ready");
}

void loop() {

  // Manual slider switch control
  if (switchChanged) {

    switchChanged = false;

    if (digitalRead(SWITCH_PIN) == LOW) {

      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);

      Serial.println("Slider switch ON -> Lights ON");
    }
    else {

      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);

      Serial.println("Slider switch OFF -> Lights OFF");
    }
  }

  // PIR motion detection
  if (motionDetected) {

    motionDetected = false;

    float lux = lightMeter.readLightLevel();

    Serial.print("Motion detected. Light level = ");
    Serial.print(lux);
    Serial.println(" lx");

    // Only auto-turn-on when dark
    if (lux < DARK_THRESHOLD) {

      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);

      Serial.println("Dark environment -> Lights ON for 5 seconds");

      delay(5000);

      // Don't turn off if slider is still ON
      if (digitalRead(SWITCH_PIN) == HIGH) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        Serial.println("5 seconds elapsed -> Lights OFF");
      }
    }
    else {
      Serial.println("Bright environment -> Lights remain OFF");
    }
  }
}
