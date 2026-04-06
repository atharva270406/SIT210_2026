 #include <Wire.h>
#include <BH1750.h>

const int pirPin = 2;
const int switchPin = 3;
const int led1 = 6;
const int led2 = 4;

BH1750 sensor;

volatile bool motion = false;
volatile bool button = false;

bool lightsOn = false;
unsigned long startTime = 0;

float threshold = 100;
int duration = 8000;

void motionDetected() {
  motion = true;
}

void switchPressed() {
  button = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(switchPin, INPUT_PULLUP);

  Wire.begin();
  sensor.begin();

  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetected, RISING);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchPressed, FALLING);

  Serial.println("System started...");
}

void loop() {

  float light = sensor.readLightLevel();

  if (motion) {
    motion = false;

    Serial.print("Motion detected, light = ");
    Serial.println(light);

    if (light < threshold) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      lightsOn = true;
      startTime = millis();
      Serial.println("Lights ON");
    } else {
      Serial.println("Enough light");
    }
  }

  if (button) {
    button = false;

    lightsOn = !lightsOn;

    digitalWrite(led1, lightsOn);
    digitalWrite(led2, lightsOn);

    Serial.println("Switch pressed");

    if (lightsOn) {
      startTime = millis();
    }
  }

  if (lightsOn && millis() - startTime > duration) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    lightsOn = false;

    Serial.println("Lights OFF");
  }

  delay(1000);
}
