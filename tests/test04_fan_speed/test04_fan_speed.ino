// Test 4: can we change the fan speed by giving it only part of the power?
//
// Report: Conclusion, "Mist and Vortex aspects" - we tried fans for the wind effect, but
// the fan did not start as a sudden enough gust, so the wind part was left out for now.
//
// How it works: analogWrite() switches the pin on and off very quickly (PWM).
// 255 = on all the time (full power), 128 = on about half the time, 0 = off.
// The fan only feels the average, so less "on" time means it spins slower.
//
// Part 1 runs by itself: 0%, 25%, 50%, 75%, 100% power, 4 seconds each.
// Part 2: in the Serial Monitor (9600 baud) type 0-9 + Enter to set the speed
//         (0 = off, 9 = full), or g + Enter for a 1-second gust at full power.
// Write down the lowest setting where the fan still starts from standstill,
// and how quickly it reaches full speed during a gust.
//
// Wiring: Grove Mini Fan on Grove port D5 (pin 5 can do PWM; on an Uno so can 3, 6, 9, 10, 11).
// A bare DC fan must NOT go straight on a pin: drive it through a transistor or MOSFET
// with a flyback diode across the fan.
//
// Written after the project (October 2026, with AI help) to document this test.

const int FAN_PIN = 5;
const int STEPS[] = {0, 25, 50, 75, 100};  // percent of full power
const int NUM_STEPS = sizeof(STEPS) / sizeof(STEPS[0]);
const unsigned long STEP_TIME = 4000;      // milliseconds
const unsigned long GUST_TIME = 1000;      // milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PIN, OUTPUT);
  analogWrite(FAN_PIN, 0);

  Serial.println("Test 4, part 1: stepping through fan power levels");
  for (int i = 0; i < NUM_STEPS; i++) {
    setFanPercent(STEPS[i]);
    delay(STEP_TIME);
  }
  setFanPercent(0);

  Serial.println("Test 4, part 2: type 0-9 for speed, or g for a gust");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();

    if (c >= '0' && c <= '9') {
      setFanPercent((c - '0') * 100 / 9);  // 0 -> 0%, 9 -> 100%
    } else if (c == 'g' || c == 'G') {
      Serial.println("Gust!");
      setFanPercent(100);
      delay(GUST_TIME);
      setFanPercent(0);
    }
  }
}

void setFanPercent(int percent) {
  int value = map(percent, 0, 100, 0, 255);
  analogWrite(FAN_PIN, value);

  Serial.print("Fan power: ");
  Serial.print(percent);
  Serial.print("% (analogWrite ");
  Serial.print(value);
  Serial.println(")");
}
