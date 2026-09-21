#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

int trig = 9;
int echo = 13;
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

#define AWS_IOT_PUBLISH_TOPIC "esp32/ultrasonic"

void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  Serial.println("Connecting to AWS IoT");

  while (!client.connect(THINGNAME)) {
    Serial.print("Connection failed, rc=");
    Serial.print(client.state());
    Serial.println(". Retrying...");
    delay(5000);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  Serial.println("AWS IoT Connected!");
}

void publishMessage(float distance) {
  StaticJsonDocument<200> doc;
  doc["distance"] = distance; // Publish distance data
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // Serialize JSON

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer); // Publish to AWS IoT
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);

  connectAWS(); // Connect to AWS IoT
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig, LOW);

  int duration = pulseIn(echo, HIGH);
  float distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  publishMessage(distance); // Send distance data to AWS IoT

  delay(1000);
}



















