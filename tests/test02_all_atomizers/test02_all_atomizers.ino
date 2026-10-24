// Test 2: all four atomizers, one at a time
//
// Report: Purchasing / Steve's notes - four Grove atomizer modules on one Grove Base Shield.
// Checks that every module works and that each port is matched to the right scent.
//
// Wiring: Grove Water Atomization modules on Grove ports D2, D4, D7 and D8.
// Open Tools > Serial Monitor at 9600 baud to see which one should be running.
//
// Written after the project (October 2026, with AI help) to document this test.

const int NUM_ATOMIZERS = 4;
const int atomizerPins[NUM_ATOMIZERS] = {2, 4, 7, 8};
const char* scentNames[NUM_ATOMIZERS] = {"Forest", "Bakery", "Beach", "Christmas"};

const unsigned long ON_TIME = 3000;  // milliseconds
const unsigned long GAP = 2000;      // milliseconds between atomizers

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_ATOMIZERS; i++) {
    pinMode(atomizerPins[i], OUTPUT);
    digitalWrite(atomizerPins[i], LOW);
  }
  Serial.println("Test 2: each atomizer runs for 3 s in turn");
}

void loop() {
  for (int i = 0; i < NUM_ATOMIZERS; i++) {
    Serial.print("Atomizer ");
    Serial.print(i + 1);
    Serial.print(" (");
    Serial.print(scentNames[i]);
    Serial.print(", pin ");
    Serial.print(atomizerPins[i]);
    Serial.println(") ON");

    digitalWrite(atomizerPins[i], HIGH);
    delay(ON_TIME);
    digitalWrite(atomizerPins[i], LOW);
    delay(GAP);
  }
  Serial.println("--- round complete ---");
}
