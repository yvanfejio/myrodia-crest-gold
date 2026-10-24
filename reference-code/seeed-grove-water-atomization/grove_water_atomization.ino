// Source: Seeed Studio wiki, Grove - Water Atomization
// https://wiki.seeedstudio.com/Grove-Water_Atomization/
// Linked from the Myrodia report (Hardware, Option 3). Unmodified example code.

/*
  Demo code for grove  atomization.
  Touch to start atomizing.
  Last modified by he
  by xiaohe
*/

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin 13 as an output.
    pinMode(A5, OUTPUT);// Set A5 as OUTPUT
    pinMode(5, INPUT); // Use digital pin 5 as output port
}

// the loop function runs over and over again forever
void loop() {
    int D2Sig = digitalRead(5);// read pin 5 signal
    if (D2Sig == 1)
    {
        /* code */
        digitalWrite(A5, HIGH);   // atomize
        delay(10000);              // wait for 10 seconds
        digitalWrite(A5, LOW);    // atomization stopped

    }
}
