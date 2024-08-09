const int R = 5;
const int G = 6;
void setup() {  // initialize digital pin 13 as an output.
   pinMode(R, OUTPUT);
   pinMode(G, OUTPUT);
}

// the loop function runs over and over again forever

void loop() {
   digitalWrite(R, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(1000); // wait for a second
   digitalWrite(R, LOW); // turn the LED off by making the voltage LOW
   delay(1000); // wait for a second
    digitalWrite(G, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(1000); // wait for a second
   digitalWrite(G, LOW); // turn the LED off by making the voltage LOW
   delay(1000); // wait for a second
}