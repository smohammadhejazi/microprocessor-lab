#include <Servo.h>

Servo motor;

const int PMW = 13;
const int POT = 0;
int value;

void setup() 
{
  motor.attach(PMW);
}

void loop() 
{
  value = analogRead(POT);
  value = map(value, 0, 1023, 0, 180);     
  motor.write(value);                 
  delay(15);    
}
