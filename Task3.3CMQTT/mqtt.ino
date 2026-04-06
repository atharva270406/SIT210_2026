#include <WiFiNINA.h>
#include <PubSubClient.h>

char ssid[] = "Telstra78A6A1";
char pass[] = "4jk6tmbw5vqrud3z";

const char* broker = "broker.emqx.io";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

const int trigPin = 7;
const int echoPin = 8;
const int led1 = 2;
const int led2 = 4;

long duration;
int distance;

String name = "ATHARVA PATEL";

int lastState = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
  }

  client.setServer(broker, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 
  duration = pulseIn(echoPin, HIGH, 25000);

  if (duration == 0) return;

  distance = duration * 0.034 / 2;

  Serial.println(distance);

  if (distance > 2 && distance < 50) {

    if (distance < 4 && lastState != 2) {
      client.publish("Atharva/Pat", name.c_str());
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      lastState = 2;
    }

    else if (distance >= 6 && distance < 15 && lastState != 1) {
      client.publish("Atharva/Wave", name.c_str());
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      lastState = 1;
    }
  }

  delay(100);   
}

void callback(char* topic, byte* payload, unsigned int length) {
  String t = String(topic);

  if (t == "Atharva/Wave") {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }

  if (t == "Atharva/Pat") {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("client456")) {
      client.subscribe("Atharva/Wave");
      client.subscribe("Atharva/Pat");
    } else {
      delay(1000);
    }
  }
}
