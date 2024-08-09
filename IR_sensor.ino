int IRSensor1 = 9;   // connect IR sensor module to Arduino pin D9
int IRSensor2 = 10;  // connect IR sensor module to Arduino pin D9
int IRSensor3 = 11;  // connect IR sensor module to Arduino pin D9
int LED = 13;        // connect LED to Arduino pin 13
void setup() {
  Serial.begin(9600);              // Init Serial at 115200 Baud Rate.
  Serial.println("Serial Working");  // Test to check if serial is working or not
  pinMode(IRSensor1, INPUT);          // IR Sensor pin INPUT
  pinMode(IRSensor2, INPUT); 
  pinMode(IRSensor3, INPUT); 
  pinMode(LED, OUTPUT);              // LED Pin Output
}
void loop() {
  int sensorStatus1 = digitalRead(IRSensor1);  // Set the GPIO as Input
  int sensorStatus2 = digitalRead(IRSensor2);
  int sensorStatus3 = digitalRead(IRSensor3);
  if (sensorStatus1 == 1)  // Check if the pin high or not
  {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW);              // LED LOW
    Serial.println("Motion Detected!");  // print Motion Detected! on the serial monitor window
  } else if (sensorStatus2 == 1)         // Check if the pin high or not
  {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW);              // LED LOW
    Serial.println("Motion Detected!");  // print Motion Detected! on the serial monitor window
  } else if (sensorStatus3 == 1)         // Check if the pin high or not
  {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW);              // LED LOW
    Serial.println("Motion Detected!");  // print Motion Detected! on the serial monitor window
  } else {
    //else turn on the onboard LED
    digitalWrite(LED, HIGH);          // LED High
    Serial.println("Motion Ended!");  // print Motion Ended! on the serial monitor window
  }
}