// Myrodia - listener (Arduino side)
//
// Waits for one-character commands from the Unity game over the USB cable:
//   '1' to '4' = turn on that scent's atomizer (and turn the others off)
//   '0'        = turn every atomizer off
//
// Hardware: Arduino Uno R3 + Grove Base Shield + 4 Grove Water Atomization modules.
// Change the pin numbers below if your modules are on different Grove ports.
//
// Only one program can use the COM port at a time, so close the Serial Monitor
// before pressing Play in Unity.
//
// Written after the project (October 2026, with AI help) to show how the
// game-to-device link described in the report works.

const int NUM_SCENTS = 4;
const int atomizerPins[NUM_SCENTS] = {2, 4, 7, 8};  // Grove ports D2, D4, D7, D8
const char* scentNames[NUM_SCENTS] = {"Forest", "Bakery", "Beach", "Christmas"};

// Safety: never run a scent for longer than this, even if the game stops sending.
// Short bursts also stop the smell lingering after the player has moved on.
const unsigned long MAX_ON_TIME = 15000;  // milliseconds

int activeScent = 0;          // 0 = nothing on, otherwise 1 to 4
unsigned long startedAt = 0;  // when the active scent was turned on

void setup() {
  Serial.begin(9600);  // must match baudRate in ScentSender.cs

  for (int i = 0; i < NUM_SCENTS; i++) {
    pinMode(atomizerPins[i], OUTPUT);
    digitalWrite(atomizerPins[i], LOW);
  }
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Myrodia ready");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command >= '1' && command <= '4') {
      startScent(command - '0');
    } else if (command == '0') {
      stopAll();
    }
    // Anything else (such as the newline the Serial Monitor adds) is ignored
  }

  if (activeScent != 0 && millis() - startedAt >= MAX_ON_TIME) {
    Serial.println("Time limit reached");
    stopAll();
  }
}

void startScent(int scent) {
  stopAll();
  digitalWrite(atomizerPins[scent - 1], HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  activeScent = scent;
  startedAt = millis();

  Serial.print("Scent on: ");
  Serial.println(scentNames[scent - 1]);
}

void stopAll() {
  for (int i = 0; i < NUM_SCENTS; i++) {
    digitalWrite(atomizerPins[i], LOW);
  }
  digitalWrite(LED_BUILTIN, LOW);

  if (activeScent != 0) {
    Serial.println("All scents off");
  }
  activeScent = 0;
}
