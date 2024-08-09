#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0");
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  while (mySerial.available())
  {
    char receivedChar = mySerial.read();
    Serial.write(receivedChar);

    // Forward received SMS as command to Code 2
    if (receivedChar == 'X' || receivedChar == 'Y' || receivedChar == 'Z')
    {
      Serial.write(receivedChar);
    }
  }
}
