#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <BH1750.h>

// ---------------- WIFI ----------------
#define WIFI_SSID "Telstra78A6A1"
#define WIFI_PASSWORD "4jk6tmbw5vqrud3z"

// ---------------- MQTT ----------------
#define MQTT_SERVER "0eed77ea4cee4319b8c99954fa0bfaa6.s1.eu.hivemq.cloud"
#define MQTT_PORT 8883   // 🔥 IMPORTANT CHANGE
#define MQTT_TOPIC "terrarium/light"

#define MQTT_USER "hivemq.webclient.1774137069393"
#define MQTT_PASSWORD "&R3yST1O0?XqpzL;ek.5"

// ---------------- OBJECTS ----------------
WiFiSSLClient wifiClient;
PubSubClient mqttClient(wifiClient);
BH1750 lightMeter;

// ---------------- LOGIC ----------------
float threshold = 100.0;
bool isSunlight = false;

// ---------------- CONNECT MQTT ----------------
void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");

    if (mqttClient.connect("ArduinoNano33IoT", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT Broker!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying...");
      delay(5000);
    }
  }
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  Wire.begin();
  lightMeter.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting WiFi...");
  }

  Serial.println("WiFi Connected");

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

  connectMQTT();
}

// ---------------- LOOP ----------------
void loop() {

  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();

  float lux = lightMeter.readLightLevel();

  Serial.print("Lux: ");
  Serial.println(lux);

  if (lux > threshold && !isSunlight) {
    Serial.println("SUNLIGHT_ON");
    mqttClient.publish(MQTT_TOPIC, "SUNLIGHT_ON");
    isSunlight = true;
  }

  else if (lux <= threshold && isSunlight) {
    Serial.println("SUNLIGHT_OFF");
    mqttClient.publish(MQTT_TOPIC, "SUNLIGHT_OFF");
    isSunlight = false;
  }

  delay(3000);
}
