#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <BH1750.h>

// WiFi credentials
#define WIFI_SSID "Telstra78A6A1"
#define WIFI_PASSWORD "4jk6tmbw5vqrud3z"

// MQTT details
#define MQTT_SERVER "0eed77ea4cee4319b8c99954fa0bfaa6.s1.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_TOPIC "terrarium/light"

#define MQTT_USER "hivemq.webclient.1774137069393"
#define MQTT_PASSWORD "&R3yST1O0?XqpzL;ek.5"

// objects
WiFiSSLClient net;
PubSubClient client(net);
BH1750 lightSensor;

// logic variables
float threshold = 100.0;
bool sunlightFlag = false;

// connect to mqtt
void connectMQTT()
{
  while (!client.connected())
  {
    Serial.print("MQTT connecting... ");

    if (client.connect("Nano33Client", MQTT_USER, MQTT_PASSWORD))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("error ");
      Serial.print(client.state());
      Serial.println(" retrying");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  Wire.begin();
  lightSensor.begin();

  // connect wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Trying WiFi...");
    delay(1000);
  }

  Serial.println("WiFi OK");

  client.setServer(MQTT_SERVER, MQTT_PORT);

  connectMQTT();
}

void loop()
{
  if (!client.connected())
  {
    connectMQTT();
  }

  client.loop();

  float luxValue = lightSensor.readLightLevel();

  Serial.print("Light: ");
  Serial.println(luxValue);

  // sunlight detected
  if (luxValue > threshold && sunlightFlag == false)
  {
    Serial.println("Sunlight ON");
    client.publish(MQTT_TOPIC, "SUNLIGHT_ON");
    sunlightFlag = true;
  }

  // sunlight stopped
  if (luxValue <= threshold && sunlightFlag == true)
  {
    Serial.println("Sunlight OFF");
    client.publish(MQTT_TOPIC, "SUNLIGHT_OFF");
    sunlightFlag = false;
  }

  delay(3000);
}
