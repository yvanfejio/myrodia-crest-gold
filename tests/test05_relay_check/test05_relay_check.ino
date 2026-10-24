// Test 5: relay module check
//
// Report: Meeting with Steve (18/03/2026) - "4 relays needed"; Purchasing - 4-channel 5V relay module.
// Clicks each relay in turn: you should hear a click and see that channel's LED light up.
//
// Wiring: relay module VCC -> 5V, GND -> GND, IN1-IN4 -> pins 9, 10, 11, 12.
//
// Most relay modules like ours are "active LOW": writing LOW turns the relay ON.
// If yours is the other way round, swap RELAY_ON and RELAY_OFF.
//
// Written after the project (October 2026, with AI help) to document this test.

const int NUM_RELAYS = 4;
const int relayPins[NUM_RELAYS] = {9, 10, 11, 12};
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_RELAYS; i++) {
    // Set the pin to OFF before making it an output, so the relay doesn't click on at start-up
    digitalWrite(relayPins[i], RELAY_OFF);
    pinMode(relayPins[i], OUTPUT);
  }
  Serial.println("Test 5: each relay on for 1 s in turn");
}

void loop() {
  for (int i = 0; i < NUM_RELAYS; i++) {
    Serial.print("Relay ");
    Serial.print(i + 1);
    Serial.println(" ON");
    digitalWrite(relayPins[i], RELAY_ON);
    delay(1000);

    digitalWrite(relayPins[i], RELAY_OFF);
    delay(500);
  }
  Serial.println("--- round complete ---");
  delay(2000);
}
