// Constant HIGH signal pin
#define SIGNAL_SOURCE_PIN 19

// Input switches
#define SWITCH_1 18
#define SWITCH_2 5
#define SWITCH_3 4
#define SWITCH_4 2
#define SWITCH_5 15

// Relay outputs
#define RELAY_1 25  // Solar
#define RELAY_2 26  // ESS
#define RELAY_3 27  // Grid
#define RELAY_4 14  // DC to AC
#define RELAY_5 12  // Load

// Buzzer pin
#define BUZZER_PIN 13

// Buzzer timer
unsigned long lastBuzzerTime = 0;
const unsigned long buzzerInterval = 15000; // 15 sec
const unsigned long buzzerDuration = 2000;  // 2 sec
bool buzzerActive = false;
unsigned long buzzerStartTime = 0;

void setup() {
  Serial.begin(115200);

  // Constant HIGH pin
  pinMode(SIGNAL_SOURCE_PIN, OUTPUT);
  digitalWrite(SIGNAL_SOURCE_PIN, HIGH);

  // Input switches
  pinMode(SWITCH_1, INPUT);
  pinMode(SWITCH_2, INPUT);
  pinMode(SWITCH_3, INPUT);
  pinMode(SWITCH_4, INPUT);
  pinMode(SWITCH_5, INPUT);

  // Output relays
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // All relays OFF initially
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
  digitalWrite(RELAY_5, LOW);

  Serial.println("Switch-to-Relay Test Mode Initialized");
}

void loop() {
  unsigned long currentTime = millis();

  // Handle buzzer
  if (!buzzerActive && currentTime - lastBuzzerTime >= buzzerInterval) {
    digitalWrite(BUZZER_PIN, HIGH);
    buzzerActive = true;
    buzzerStartTime = currentTime;
    lastBuzzerTime = currentTime;
    Serial.println("Buzzer ON");
  }

  if (buzzerActive && currentTime - buzzerStartTime >= buzzerDuration) {
    digitalWrite(BUZZER_PIN, LOW);
    buzzerActive = false;
    Serial.println("Buzzer OFF");
  }

  // Read switches and control relays
  digitalWrite(RELAY_1, digitalRead(SWITCH_1));
  digitalWrite(RELAY_2, digitalRead(SWITCH_2));
  digitalWrite(RELAY_3, digitalRead(SWITCH_3));
  digitalWrite(RELAY_4, digitalRead(SWITCH_4));
  digitalWrite(RELAY_5, digitalRead(SWITCH_5));

  // Debug messages
  Serial.print("Relays: ");
  Serial.print(digitalRead(SWITCH_1)); Serial.print(" ");
  Serial.print(digitalRead(SWITCH_2)); Serial.print(" ");
  Serial.print(digitalRead(SWITCH_3)); Serial.print(" ");
  Serial.print(digitalRead(SWITCH_4)); Serial.print(" ");
  Serial.println(digitalRead(SWITCH_5));

  delay(300);  // Small delay for switch debounce
}
