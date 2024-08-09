
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9  // Configurable, see typical pin layout above
#define SS_PIN 10  // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
byte accessUID1[4] = { 0xF3, 0x96, 0x46, 0xF7 };
byte accessUID2[4] = { 0xF3, 0x47, 0xBD, 0x24 };
byte accessUID3[4] = { 0xF3, 0x3D, 0xB7, 0x1C };

int IRSensor1 = A1;  // connect IR sensor module to Arduino pin D9
int IRSensor2 = A2;  // connect IR sensor module to Arduino pin D9
int IRSensor3 = A3;  // connect IR sensor module to Arduino pin D9

#include <Servo.h>

Servo motor1;
Servo motor2;

int pos1 = 100;
int pos2 = 100;

#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2);  //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial)
    ;                                 // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                        // Init SPI bus
  mfrc522.PCD_Init();                 // Init MFRC522
  delay(4);                           // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  pinMode(IRSensor1, INPUT);  // IR Sensor pin INPUT
  pinMode(IRSensor2, INPUT);
  pinMode(IRSensor3, INPUT);

  pinMode(6, OUTPUT);  //Green
  pinMode(5, OUTPUT);  //Red

  motor1.attach(7);  //D9
  motor2.attach(8);  //D10
  motor1.write(pos1);
  motor2.write(pos2);


  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT");  //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+917404405272\"");  //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("ONLINE");  //text content
  updateSerial();
  mySerial.write(26);
}
void moveMotor(Servo &motor, int &pos, int targetPos, const char *motorName) {
  Serial.print("Moving ");
  Serial.print(motorName);
  Serial.print(" from ");
  Serial.print(pos);
  Serial.print(" to ");
  Serial.println(targetPos);

  int step = (targetPos > pos) ? 1 : -1;  // Determine if we're moving up or down

  for (int i = pos; i != targetPos; i += step) {
    motor.write(i);
    delay(15);
  }
  motor.write(targetPos);  // Make sure we reach the exact target position
  pos = targetPos;
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read());  //Forward what Software Serial received to Serial Port
  }
}

void loop() {
  int sensorStatus1 = digitalRead(IRSensor1);  // Set the GPIO as Input
  int sensorStatus2 = digitalRead(IRSensor2);
  int sensorStatus3 = digitalRead(IRSensor3);
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  if (mfrc522.uid.uidByte[0] == accessUID1[0]
      && mfrc522.uid.uidByte[1] == accessUID1[1]
      && mfrc522.uid.uidByte[2] == accessUID1[2]
      && mfrc522.uid.uidByte[3] == accessUID1[3]) {
    if (sensorStatus1 == 1) {
      Serial.println("Train 1");

      moveMotor(motor1, pos1, 99, "Motor 1");

      digitalWrite(5, HIGH);
      delay(5000);  // wait for a second
      digitalWrite(5, LOW);

      mySerial.println("AT+CMGS=\"+917404405272\"");  // Replace ZZ with country code and xxxxxxxxxxx with phone number
      updateSerial();
      mySerial.print("GO");  // Text content
      updateSerial();
      mySerial.write(26);
      delay(2000);  // Add a delay to avoid rapid SMS sending (optional)
    }
    if (sensorStatus1 == 0) {
      digitalWrite(6, HIGH);
      delay(5000);  // wait for a second
      digitalWrite(6, LOW);

      mySerial.println("AT+CMGS=\"+917404405272\"");  // Replace ZZ with country code and xxxxxxxxxxx with phone number
      updateSerial();
      mySerial.print("STOP");  // Text content
      updateSerial();
      mySerial.write(26);
      delay(2000);  // Add a delay to avoid rapid SMS sending (optional)
    }
  }
  if (mfrc522.uid.uidByte[0] == accessUID2[0]
      && mfrc522.uid.uidByte[1] == accessUID2[1]
      && mfrc522.uid.uidByte[2] == accessUID2[2]
      && mfrc522.uid.uidByte[3] == accessUID2[3]) {

    if (sensorStatus2 == 1) {
      Serial.println("Train 2");



      moveMotor(motor1, pos1, 118, "Motor 1");
      delay(500);
      moveMotor(motor2, pos2, 118, "Motor 2");

      digitalWrite(5, HIGH);
      delay(5000);  // wait for a second
      digitalWrite(5, LOW);

      mySerial.println("AT+CMGS=\"+917404405272\"");  // Replace ZZ with country code and xxxxxxxxxxx with phone number
      updateSerial();
      mySerial.print("GO");  // Text content
      updateSerial();
      mySerial.write(26);
      delay(2000);  // Add a delay to avoid rapid SMS sending (optional)
    }
    if (sensorStatus2 == 0) {
      digitalWrite(6, HIGH);
      delay(5000);  // wait for a second
      digitalWrite(6, LOW);

      mySerial.println("AT+CMGS=\"+917404405272\"");  // Replace ZZ with country code and xxxxxxxxxxx with phone number
      updateSerial();
      mySerial.print("STOP");  // Text content
      updateSerial();
      mySerial.write(26);
      delay(2000);  // Add a delay to avoid rapid SMS sending (optional)
    }
  }
  if (mfrc522.uid.uidByte[0] == accessUID3[0]
      && mfrc522.uid.uidByte[1] == accessUID3[1]
      && mfrc522.uid.uidByte[2] == accessUID3[2]
      && mfrc522.uid.uidByte[3] == accessUID3[3]) {

    if (sensorStatus3 == 1) {
      Serial.println("Train 3");

      moveMotor(motor1, pos1, 118, "Motor 1");
      delay(500);
      moveMotor(motor2, pos2, 100, "Motor 2");

      digitalWrite(5, HIGH);
      delay(5000);  // wait for a second
      digitalWrite(5, LOW);

      mySerial.println("AT+CMGS=\"+917404405272\"");  // Replace ZZ with country code and xxxxxxxxxxx with phone number
      updateSerial();
      mySerial.print("GO");  // Text content
      updateSerial();
      mySerial.write(26);
      delay(2000);  // Add a delay to avoid rapid SMS sending (optional)
    }
    if (sensorStatus3 == 0) {
      digitalWrite(6, HIGH);
      delay(5000);  // wait for a second
      digitalWrite(6, LOW);

      mySerial.println("AT+CMGS=\"+917404405272\"");  // Replace ZZ with country code and xxxxxxxxxxx with phone number
      updateSerial();
      mySerial.print("STOP");  // Text content
      updateSerial();
      mySerial.write(26);
      delay(2000);  // Add a delay to avoid rapid SMS sending (optional)
    }
  }
  updateSerial();
  mfrc522.PICC_HaltA();
}