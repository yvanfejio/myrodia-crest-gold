# Myrodia – CREST Gold (Big Bang Competition), Group 3

Myrodia (Greek for "smell") is a proof-of-concept 4D experience device. It sits beside a computer and
releases scent and mist in time with what happens in a game. A Unity game sends signals over USB
to an Arduino. The Arduino then switches on the ultrasonic atomizer for the scent that matches the
player's current in-game environment.

## The project document

- **Working document (Google Doc):** https://docs.google.com/document/d/1ugFnCQpechNtZWfM6atZNhy444dmoCYNcIgQFImnIb4/edit?usp=sharing
- **PDF copy in this repo:** [docs/Myrodia_CREST_Gold_Report.pdf](docs/Myrodia_CREST_Gold_Report.pdf)
- **Video explanation of the game and its connection to the device:** [My Movie 2.mov (Google Drive)](https://drive.google.com/file/d/1kBp9Sm3sg4ZERz5Lc0UUaBBMcqcNniZl/view?usp=sharing)

The document covers our aims, the meeting log, mentor meetings, the science, the issues we hit and how we
solved them, our range of approaches, the scents, the game, the hardware and our conclusion.

## The team

| Name | Role |
| --- | --- |
| Rami Al-Kheralla | Team lead: brought the disciplines together, ran meetings, tracked progress |
| Yvan Fejio-Tiofack | Tech lead: designed the electronics and linked them to the game |
| Veer Parekh | Physical operation lead: built the game and its environments |
| Sai Kaushal Chilamakuru | Chemical lead: sourced the scents and tested concentrations |

## How it works

```
Unity game (C#)  --USB serial, one character e.g. "1"-->  Arduino Uno (C++)  -->  Grove atomizer for that scent
```

1. **Sender (Unity, C#):** when the character walks into an invisible trigger box for an environment,
   a script sends a single character (such as `"1"`) to the USB serial port.
2. **Bridge (USB cable):** a one-way serial link from Unity to the Arduino, at a fixed port and baud rate.
3. **Listener (Arduino, C++):** the Arduino waits for serial data. When a character such as `"1"` or `"2"`
   arrives, an `if` statement powers the matching atomizer.

| Game environment | Scent |
| --- | --- |
| Forest | [Forgotten Ferns & Oak](https://purescented.com/forgotten-ferns-oak-fragrance-oil/) |
| Bakery | [Baked Bread](https://purescented.com/baked-bread-fragrance-oil/) |
| Beach | [Ocean Luna](https://purescented.com/ocean-luna-fragrance-oil/) |
| Christmas | [A Merry Morning](https://purescented.com/a-merry-morning-fragrance-oil/) |

Scents are diluted at 4 parts scent to 6 parts water. That mix could be smelled 50 cm from the source within 8 seconds.

## Repository layout

```
docs/                 PDF copy of the project document
code/arduino/         Arduino sketch that listens for the game and switches the atomizers
code/unity/           Unity C# scripts that send a command when the player enters an environment
tests/                Arduino sketches (and one Unity script) for the tests described in the report
reference-code/       Example code from the tutorials linked in the document (not written by the team)
```

## Code and tests

> **Note:** the code in `code/` and `tests/` was written after the project, in October 2026, with
> AI help. It shows how the system described in the report works and documents the tests the report
> describes. It is not the original code from the project. Every sketch compiles for the Arduino Uno.

### Wiring used in the code

| Part | Grove Base Shield port / Arduino pin |
| --- | --- |
| Atomizer 1 – Forest | D2 |
| Atomizer 2 – Bakery | D4 |
| Atomizer 3 – Beach | D7 |
| Atomizer 4 – Christmas | D8 |
| Grove Mini Fan (test 4) | D5 (a PWM pin) |
| Relay module IN1–IN4 (test 5) | pins 9, 10, 11, 12 |

If your parts are on different ports, change the pin numbers at the top of each sketch.

### Running the game and device together

1. Open [code/arduino/myrodia_listener/myrodia_listener.ino](code/arduino/myrodia_listener/myrodia_listener.ino)
   in the Arduino IDE, choose **Tools > Board > Arduino Uno** and the right **Port**, and upload it.
2. In Unity, copy [ScentSender.cs](code/unity/ScentSender.cs) and [ScentZone.cs](code/unity/ScentZone.cs) into `Assets/`.
3. Set **Edit > Project Settings > Player > Other Settings > Api Compatibility Level** to **.NET Framework**.
4. Add an empty GameObject with `ScentSender` on it and set **Port Name** to the Arduino's port (for example `COM3`).
5. For each environment, add an invisible cube with **Is Trigger** ticked and a `ScentZone`
   (1 = Forest, 2 = Bakery, 3 = Beach, 4 = Christmas). The player must have the tag `Player`.
6. **Close the Arduino Serial Monitor**, then press Play. Only one program can use the port at a time.

The Arduino restarts for about 2 seconds when Unity opens the port, so start the player outside the scent zones.

| Command sent by Unity | What the Arduino does |
| --- | --- |
| `1`–`4` | Turns on that scent's atomizer and turns the others off |
| `0` | Turns every atomizer off. Sent when the player leaves a zone and when the game stops (emergency stop) |
| *(15 seconds with no change)* | Turns the scent off by itself so it never runs on |

### Tests

| Test | What it checks | Where it comes from in the report |
| --- | --- | --- |
| [test01_atomizer_single](tests/test01_atomizer_single/test01_atomizer_single.ino) | One atomizer switches on and off, first with water, then with scent | Meeting 8 (13/04/26) |
| [test02_all_atomizers](tests/test02_all_atomizers/test02_all_atomizers.ino) | All four atomizers work and are on the right ports | Purchasing, Steve's notes |
| [test03_scent_spread_timer](tests/test03_scent_spread_timer/test03_scent_spread_timer.ino) | Time until a mix can be smelled 50 cm away (goal: under 8 s) | Scents (4:6 scent to water) |
| [test04_fan_speed](tests/test04_fan_speed/test04_fan_speed.ino) | Fan speed when given only part of the power (PWM), and how fast a gust starts | Conclusion: Mist and Vortex aspects |
| [test05_relay_check](tests/test05_relay_check/test05_relay_check.ino) | Each of the 4 relay channels clicks on and off | Meeting with Steve (18/03/2026) |
| [test06_serial_link](tests/test06_serial_link/test06_serial_link.ino) + [SerialTestPanel.cs](tests/unity/SerialTestPanel.cs) | The Arduino receives what Unity sends, before the atomizers are connected | Meetings 10 and 11 |

Upload a test sketch, then open **Tools > Serial Monitor** at **9600 baud** to see what it is doing.

## Reference code from the linked tutorials

These are the unmodified examples from the hardware pages linked in the document. Each file names its source.

- [reference-code/keyestudio-atomization/keyestudio_atomization.ino](reference-code/keyestudio-atomization/keyestudio_atomization.ino):
  Keyestudio KS6082 atomization module ([tutorial](https://docs.keyestudio.com/projects/KS6082/en/latest/docs/Tutorial.html))
- [reference-code/seeed-grove-water-atomization/grove_water_atomization.ino](reference-code/seeed-grove-water-atomization/grove_water_atomization.ino):
  Grove – Water Atomization ([Seeed wiki](https://wiki.seeedstudio.com/Grove-Water_Atomization/))

The Unity-to-Arduino serial approach follows [Bring your Unity Games to Life with real-world Hardware](https://www.youtube.com/watch?v=t4dpD_X7DOw).
That video teaches the code on screen, so there is no code to download from it.

## Hardware

- Arduino Uno R3 with a 12 V 2 A barrel-jack power supply ([The Pi Hut](https://thepihut.com/products/12v-2a-power-supply-with-2-1mm-barrel-jack))
- Grove Base Shield for Arduino ([Farnell](https://uk.farnell.com/seeed-studio/103030000/grove-base-shield-arduino-dev/dp/3932129))
- Grove Water Atomization modules × 4 ([Farnell](https://uk.farnell.com/seeed-studio/101020090/water-atomization-module-arduino/dp/4007693), [wiki](https://wiki.seeedstudio.com/Grove-Water_Atomization/))
- Grove Mini Fan ([Farnell](https://uk.farnell.com/search?st=grove+mini+fan), [wiki](https://wiki.seeedstudio.com/Grove-Mini_Fan/#features))
- 2- or 4-channel 5 V relay module (optocoupler-isolated), flyback diodes
- Breadboard, jumper wires, foam scent sticks, enclosure, fan mount, silicone tubing

## Game assets (Sketchfab)

| Environment | Assets |
| --- | --- |
| Forest | [Grass](https://sketchfab.com/3d-models/grass-f2f2bddb2728483a9105c5f5114eb15e), [Tiger](https://sketchfab.com/3d-models/running-tiger-fc2c7fd74dd04e39935803b884c77258), [Tree](https://sketchfab.com/3d-models/forest-demo-1269b7e00f9d4ce09931c0c95967bc33) |
| Bakery | [Bakery](https://sketchfab.com/3d-models/candy-shop-draft-7ff4e5c0d2c74fe29461e34629c2274b), [Pastries](https://sketchfab.com/3d-models/game-ready-bakery-asset-pack-5fffce6e9a2d4c9b999e0f574d0b05f1), [Car](https://sketchfab.com/3d-models/car-scene-b7b32eaca80d460c9338197e2c9d1408) |
| Beach | [Sand](https://sketchfab.com/3d-models/sand-d491e5f026234eaea7b3a36fd48da21b), [Pool](https://sketchfab.com/3d-models/giant-swimming-pool-2dc3c7053131409a998aea9671630dd9), [Table set](https://sketchfab.com/3d-models/beach-table-e559392994e04527b3f5ee35a8c3c418), [Sun](https://sketchfab.com/3d-models/cloud-sun-anim-1aac7ba1e8e84af5a8ea66aab9a9a66d) |
| Christmas | [Hut](https://sketchfab.com/3d-models/winter-country-house-7673ffdea07e4a2b9e6dfc31f16a5eee), [Snowglobe](https://sketchfab.com/3d-models/christmas-ball-36868988285f4b60b3e389e1aa1bab3f) |

## Unity tutorials we used

- https://www.youtube.com/watch?v=3wcMtJK8iIY
- https://www.youtube.com/watch?v=FiW69KIsQz0
- [YouTube search: how to import asset into Unity](https://www.youtube.com/results?search_query=how+to+import+asset+into+unity)

## Thanks

Thanks to Steve Smythe, our electrical engineering mentor, and to Mr Mohan, our supervisor.
