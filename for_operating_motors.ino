#include <Servo.h>

Servo motor1;
Servo motor2;

int pos1 = 100;
int pos2 = 100;

void setup()
{
  Serial.begin(9600);
  motor1.attach(9);
  motor2.attach(10);
  motor1.write(pos1);
  motor2.write(pos2);
}

void moveMotor(Servo &motor, int &pos, int targetPos, const char *motorName)
{
  Serial.print("Moving ");
  Serial.print(motorName);
  Serial.print(" from ");
  Serial.print(pos);
  Serial.print(" to ");
  Serial.println(targetPos);

  int step = (targetPos > pos) ? 1 : -1; // Determine if we're moving up or down

  for (int i = pos; i != targetPos; i += step)
  {
    motor.write(i);
    delay(15);
  }
  motor.write(targetPos); // Make sure we reach the exact target position
  pos = targetPos;
}

void loop()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();
    delay(500);
    

    if (command == 'X')
    {
      moveMotor(motor1, pos1, 99, "Motor 1");
    }
    else if (command == 'Y')
    {
      moveMotor(motor1, pos1, 118, "Motor 1");
      delay(500);
      moveMotor(motor2, pos2, 118, "Motor 2");
    }
    else if (command == 'Z')
    {
      moveMotor(motor1, pos1, 118, "Motor 1");
      delay(500);
      moveMotor(motor2, pos2, 100, "Motor 2");
    }
  }
}
