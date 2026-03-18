#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

char ssid[] = "iPhone";
char pass[] = "12345678";

WiFiClient client;
unsigned long channel = 3296072;         // ThingSpeak channel number
const char* apiKey = "7VJAEBNXSCY5C4CM"; // ThingSpeak write API key

DHT dht(DHTPIN, DHTTYPE);
int lightSensor = A0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Trying to connect...");
  }
  Serial.println("WiFi connected!");

  ThingSpeak.begin(client);
}

void loop() {
  float temp = dht.readTemperature();   // read temperature
  float hum = dht.readHumidity();       // read humidity
  int light = analogRead(lightSensor);  // read light level

  // Print to serial monitor
  Serial.print("Temperature: "); Serial.print(temp); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(hum); Serial.println(" %");
  Serial.print("Light level: "); Serial.println(light);

  // Send to ThingSpeak
  ThingSpeak.setField(1, temp);   // field 1 = temperature
  ThingSpeak.setField(4, hum);    // field 2 = humidity
  ThingSpeak.setField(3, light);  // field 3 = light
  ThingSpeak.writeFields(channel, apiKey);

  delay(30000); // wait 30 seconds
}
