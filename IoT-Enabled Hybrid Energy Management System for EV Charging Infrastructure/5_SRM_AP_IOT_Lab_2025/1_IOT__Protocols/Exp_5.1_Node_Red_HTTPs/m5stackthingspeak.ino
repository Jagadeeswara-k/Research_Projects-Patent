#include <M5Stack.h>
#include <WiFi.h>
#include <ThingSpeak.h>

const char *ssid = "wifi hello";       // Replace with your WiFi SSID
const char *password = "94949494"; // Replace with your WiFi password
const char *thingSpeakAPIKey = "164FTE3FJEW2G2F2"; // Replace with your ThingSpeak API key

const int analogPin = 36;
const int digitalPin = 2;

WiFiClient client;

void setup() {
  // Initialize M5Stack and LCD
  M5.begin();
  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.print("MICROPHONE");

  // Set up pin modes
  pinMode(digitalPin, INPUT_PULLUP);
  dacWrite(25, 0);

  // Initialize Serial communication
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Print IP address once connected
  Serial.println();
  Serial.print("Connected to WiFi. IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

uint16_t a_data;
uint16_t d_data;

void loop() {
  // Read analog and digital data
  a_data = analogRead(analogPin);
  d_data = digitalRead(digitalPin);

  // Print values to Serial Monitor
  Serial.print("analog ");
  Serial.print(a_data);
  Serial.print(" digital ");
  Serial.println(d_data);

  // Display values on M5Stack LCD
  M5.Lcd.setCursor(30, 20, 4);
  M5.Lcd.printf("analog %d digital %d\n", a_data, d_data);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, a_data); // Send analog data to field 1
  ThingSpeak.setField(2, d_data); // Send digital data to field 2

  // Update ThingSpeak (write data to channel)
  int responseCode = ThingSpeak.writeFields(2805296, thingSpeakAPIKey);  // Replace Your_Channel_ID with your actual channel ID

  // Check for successful data send
  if (responseCode == 200) {
    Serial.println("Data sent successfully to ThingSpeak!");
  } else {
    Serial.print("Failed to send data. HTTP response code: ");
    Serial.println(responseCode);
  }

  delay(200); // Delay before sending next data (200 ms)
}