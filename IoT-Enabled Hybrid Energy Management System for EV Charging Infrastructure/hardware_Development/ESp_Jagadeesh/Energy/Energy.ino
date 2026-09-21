// ESP32 Relay Control via Switch
// Signal source → GPIO 19 (always HIGH)
// Switch input → GPIO 18 (reads HIGH when switch is closed)
// Relay control → GPIO 23

#define SIGNAL_SOURCE_PIN 19     // Constant HIGH output
#define SIGNAL_INPUT_PIN 18      // Reads HIGH when switch is closed
#define RELAY_CONTROL_PIN 25     // Relay control pin

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);
  Serial.println("System Initialized");

  // Setup pins
  pinMode(SIGNAL_SOURCE_PIN, OUTPUT);
  digitalWrite(SIGNAL_SOURCE_PIN, HIGH);   // Provide constant HIGH signal

  pinMode(SIGNAL_INPUT_PIN, INPUT_PULLDOWN);  // Enable internal pulldown resistor

  pinMode(RELAY_CONTROL_PIN, OUTPUT);
  digitalWrite(RELAY_CONTROL_PIN, LOW);    // Ensure relay is OFF initially
}

void loop() {
  int signal = digitalRead(SIGNAL_INPUT_PIN);

  if (signal == HIGH) {
    digitalWrite(RELAY_CONTROL_PIN, HIGH);  // Relay ON
    Serial.println("Switch ON → Relay ON");
  } else {
    digitalWrite(RELAY_CONTROL_PIN, LOW);   // Relay OFF
    Serial.println("Switch OFF → Relay OFF");
  }

  delay(100); // Check every 100ms
}
