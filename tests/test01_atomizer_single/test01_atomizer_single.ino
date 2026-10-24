// Test 1: one atomizer on and off
//
// Report: Meeting 8 (13/04/26) - the first prototype was tried with plain water,
// then with scent mixed in.
//
// Wiring: one Grove Water Atomization module on Grove port D2.
// Open Tools > Serial Monitor at 9600 baud to see what it is doing.
//
// Written after the project (October 2026, with AI help) to document this test.

const int ATOMIZER_PIN = 2;
const unsigned long ON_TIME = 5000;   // milliseconds
const unsigned long OFF_TIME = 5000;  // milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(ATOMIZER_PIN, OUTPUT);
  digitalWrite(ATOMIZER_PIN, LOW);
  Serial.println("Test 1: atomizer on for 5 s, off for 5 s");
}

void loop() {
  Serial.println("Atomizer ON");
  digitalWrite(ATOMIZER_PIN, HIGH);
  delay(ON_TIME);

  Serial.println("Atomizer OFF");
  digitalWrite(ATOMIZER_PIN, LOW);
  delay(OFF_TIME);
}
