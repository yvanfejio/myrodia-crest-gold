// Source: Keyestudio KS6082 atomization module tutorial
// https://docs.keyestudio.com/projects/KS6082/en/latest/docs/Tutorial.html
// Linked from the Myrodia report (Hardware, Option 1). Unmodified example code.

int atomization = 3;  //Set the pin of the atomization module
void setup() {
  pinMode(atomization, OUTPUT);//set the pin to output
  digitalWrite(atomization, HIGH);//set the pin to high  
}

void loop() {
  //Turn on the atomization module, equivalent to pressing a button
  digitalWrite(atomization, LOW);   
  delay(200);  
  digitalWrite(atomization, HIGH); 
  delay(3000); 
  //Turn off the atomization module, equivalent to pressing the button again
  digitalWrite(atomization, LOW); 
  delay(200); 
  digitalWrite(atomization, HIGH);   
  delay(1000);
}
