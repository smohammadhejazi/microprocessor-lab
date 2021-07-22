//Seyyed Mohammad Hejazi Hoseini
//1400- Spring

#include <Servo.h>

Servo servo;

const int SERVO_PMW = 13;
const int DC_MOTOR_B = 11;
const int DC_MOTOR_F = 10;
const int LIGHTS = 9;
const int HORN = 8;

char next_byte;
boolean lights = false;
unsigned long timer = 0;

void serial_flush(void) {
  while (Serial.available()) Serial.read();
}

void setup() 
{
  Serial.begin(9600);
  
  servo.attach(SERVO_PMW);

  pinMode(DC_MOTOR_F, OUTPUT);
  pinMode(DC_MOTOR_B, OUTPUT);
  pinMode(LIGHTS, OUTPUT);
  pinMode(HORN, OUTPUT);
}

void loop() 
{
  if (Serial.available())
  {
    timer = millis();
    while((Serial.available()) && millis() - timer <= 100)
    {
      next_byte = Serial.read();
      if (next_byte == 'w')
      {
        digitalWrite(DC_MOTOR_F, HIGH);
      }
      else if (next_byte == 's')
      {
        digitalWrite(DC_MOTOR_B, HIGH);
      }
      else if (next_byte == '2')
      {
        servo.writeMicroseconds(1750);
      }
      else if (next_byte == '1')
      {
        servo.writeMicroseconds(1850);
      }
      else if (next_byte == '3')
      {
        servo.writeMicroseconds(1250);
      }
      else if (next_byte == '4')
      {
        servo.writeMicroseconds(1150);
      }
      else if (next_byte == 'h')
      {
        Serial.println("Pressed Honk");
        digitalWrite(HORN, HIGH);
      }
      else if (next_byte == 'l')
      {
        Serial.println("Toggle Lights");
        lights = !lights;
        digitalWrite(LIGHTS, HIGH);
      }
      else if (next_byte == 'k')
      {
        Serial.println("Pressed lights");
        digitalWrite(LIGHTS, HIGH);
      }
    }
    serial_flush();
    delay(130);
  }
  else
  {
    if (lights == false)
    {
      digitalWrite(LIGHTS, LOW);
    }
    digitalWrite(HORN, LOW);
    digitalWrite(DC_MOTOR_F, LOW);
    digitalWrite(DC_MOTOR_B, LOW);
    servo.writeMicroseconds(1500);
  }
}
