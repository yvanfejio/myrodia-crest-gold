// Test 6: does the Arduino receive what Unity sends?
//
// Report: Meetings 10 and 11 (June-July 2026) - connecting the game to the Arduino over USB.
// Tests the link on its own, before any atomizers are plugged in.
//
// How to use:
//   - Type 1, 2, 3, 4 or 0 in the Serial Monitor (9600 baud) and press Enter, or
//   - close the Serial Monitor, press Play in Unity and click the SerialTestPanel buttons.
// The built-in LED (pin 13) blinks once for 1, twice for 2, and so on. 0 gives one long blink.
//
// Written after the project (October 2026, with AI help) to document this test.

void setup() {
  Serial.begin(9600);  // must match baudRate in ScentSender.cs
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Test 6: waiting for 0-4");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();

    if (c >= '1' && c <= '4') {
      Serial.print("Got: ");
      Serial.println(c);
      blink(c - '0');
    } else if (c == '0') {
      Serial.println("Got: 0 (all off)");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    } else if (c != '\n' && c != '\r') {
      Serial.print("Ignored character code ");
      Serial.println((int)c);
    }
  }
}

void blink(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}
