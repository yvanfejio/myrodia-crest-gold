// Test 3: how long until the scent can be smelled?
//
// Report: Scents - we tried mixes from 1:9 up to 9:1 scent to water and aimed for the scent
// to be smelled 50 cm from the source within 8 seconds. 4 parts scent to 6 parts water was best.
//
// How to use:
//   1. Fill one atomizer with the mix being tested and stand 50 cm away.
//   2. In the Serial Monitor (9600 baud), type the atomizer number (1-4) and press Enter.
//   3. As soon as you can smell it, type s and press Enter.
//   4. Copy the result line into the results table, then air the room before the next run.
//
// Wiring: Grove Water Atomization modules on Grove ports D2, D4, D7 and D8.
//
// Written after the project (October 2026, with AI help) to document this test.

const int NUM_SCENTS = 4;
const int atomizerPins[NUM_SCENTS] = {2, 4, 7, 8};
const char* scentNames[NUM_SCENTS] = {"Forest", "Bakery", "Beach", "Christmas"};

const unsigned long TARGET_TIME = 8000;  // goal: smelled within 8 s
const unsigned long MAX_RUN = 15000;     // give up after 15 s

int running = 0;                  // 0 = nothing running, otherwise 1 to 4
unsigned long startedAt = 0;
unsigned long nextSecond = 0;     // when to print the next seconds count

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_SCENTS; i++) {
    pinMode(atomizerPins[i], OUTPUT);
    digitalWrite(atomizerPins[i], LOW);
  }
  Serial.println("Test 3: scent spread timer");
  Serial.println("Type 1-4 + Enter to start an atomizer, then s + Enter when you smell it.");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c >= '1' && c <= '4') {
      startRun(c - '0');
    } else if (c == 's' || c == 'S') {
      smelled();
    }
  }

  if (running != 0) {
    unsigned long elapsed = millis() - startedAt;

    if (elapsed >= nextSecond) {
      Serial.print(nextSecond / 1000);
      Serial.println(" s");
      nextSecond += 1000;
    }

    if (elapsed >= MAX_RUN) {
      stopRun();
      Serial.println("Not smelled within 15 s - FAIL (try a stronger mix)");
    }
  }
}

void startRun(int scent) {
  stopRun();
  running = scent;
  startedAt = millis();
  nextSecond = 0;
  digitalWrite(atomizerPins[scent - 1], HIGH);

  Serial.print("Started atomizer ");
  Serial.print(scent);
  Serial.print(" (");
  Serial.print(scentNames[scent - 1]);
  Serial.println(")");
}

void smelled() {
  if (running == 0) return;

  unsigned long elapsed = millis() - startedAt;
  int scent = running;
  stopRun();

  Serial.print("RESULT: ");
  Serial.print(scentNames[scent - 1]);
  Serial.print(" smelled at 50 cm after ");
  Serial.print(elapsed / 1000.0, 1);
  Serial.print(" s - ");
  Serial.println(elapsed <= TARGET_TIME ? "PASS" : "FAIL");
}

void stopRun() {
  for (int i = 0; i < NUM_SCENTS; i++) {
    digitalWrite(atomizerPins[i], LOW);
  }
  running = 0;
}
