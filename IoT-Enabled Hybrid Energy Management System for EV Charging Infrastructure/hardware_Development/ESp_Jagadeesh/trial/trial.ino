#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "wifi";
const char* password = "round123-";

// ThingSpeak details
const char* server = "http://api.thingspeak.com/update";
String apiKey = "LO86IXIHMOMGTZR4";

// Analog input pins
const int ESS_voltagePin = 34;  // ESS voltage
const int ESS_currentPin = 35;  // ESS current
const int Grid_voltagePin = 32; // Grid voltage
const int Grid_currentPin = 33; // Grid current
const int SIGNAL_PIN = 19;      // Optional HIGH signal pin

// Voltage divider resistors
const float R1 = 30000.0;  // 30kΩ
const float R2 = 7500.0;   // 7.5kΩ

// ACS712 current sensor sensitivity (in mV per amp)
const float sensitivity = 0.185; // 185mV per Amp for 5A version

void setup() {
  Serial.begin(115200);
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, HIGH);  // Constant HIGH signal

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Wi-Fi Connection Failed");
  }
}

void loop() {
  // Read analog values from pins
  int essRawV = analogRead(ESS_voltagePin);
  int essRawC = analogRead(ESS_currentPin);
  int gridRawV = analogRead(Grid_voltagePin);
  int gridRawC = analogRead(Grid_currentPin);

  // Convert to real voltage (based on divider)
  float essV = (essRawV / 4095.0) * 3.3 * ((R1 + R2) / R2);
  float gridV = (gridRawV / 4095.0) * 3.3 * ((R1 + R2) / R2);

  // Calculate current (based on ACS712 - convert ADC to voltage, then to current)
  float essCurrentV = (essRawC / 4095.0) * 3.3;  // ADC to voltage (0-3.3V)
  float essCurrent = (essCurrentV - 2.5) / sensitivity; // Calculate current (in Amps)

  float gridCurrentV = (gridRawC / 4095.0) * 3.3;  // ADC to voltage (0-3.3V)
  float gridCurrent = (gridCurrentV - 2.5) / sensitivity; // Calculate current (in Amps)

  // Print the values to Serial Monitor
  Serial.println("----- ESS & GRID PARAMETERS -----");
  Serial.print("ESS Voltage: "); Serial.print(essV, 2); Serial.println(" V");
  Serial.print("ESS Current: "); Serial.print(essCurrent, 2); Serial.println(" A");

  Serial.print("Grid Voltage: "); Serial.print(gridV, 2); Serial.println(" V");
  Serial.print("Grid Current: "); Serial.print(gridCurrent, 2); Serial.println(" A");
  Serial.println("----------------------------------");

  // Send to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = server;
    url += "?api_key=" + apiKey;
    url += "&field1=" + String(essV, 2);      // ESS Voltage
    url += "&field2=" + String(essCurrent, 2); // ESS Current
    url += "&field3=" + String(gridV, 2);     // Grid Voltage
    url += "&field4=" + String(gridCurrent, 2); // Grid Current

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("✅ Data sent to ThingSpeak");
    } else {
      Serial.print("❌ ThingSpeak Error: ");
      Serial.println(httpCode);
    }

    http.end();
  } else {
    Serial.println("⚠️ Wi-Fi disconnected");
  }

  delay(20000);  // 20 sec delay before next update
}
