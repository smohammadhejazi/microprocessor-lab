#include <Servo.h>

const int PMW = 13;

Servo motor;

void setup() 
{
  motor.attach(PMW);
}

void loop()
{
  for(int i = 1500; i <= 1750; i++)
  {
      motor.writeMicroseconds(i);
      delay(5);
  }
  for(int i = 1750; i >= 1500; i--)
  {
      motor.writeMicroseconds(i);
      delay(5);
  }
}
