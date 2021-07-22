#include <Keypad.h>
#include <Servo.h>

const int PMW = 13;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = 
{
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}  
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo motor;

char next_byte;
int value;
String degree_str = "";
int degree_int;

void setup() 
{
  motor.attach(PMW);
  Serial3.begin(9600);
}

void loop() 
{
  next_byte = Serial3.read();
  if (next_byte != -1)
  {
    if (next_byte == 13)
    { 
      degree_int = degree_str.toInt();
      if (degree_int >= -180 && degree_int <= 180)
      {
        degree_int *= -1;
        value = map(degree_int, -180, 180, 1000, 2000);
        motor.writeMicroseconds(value);
      }
           
      Serial3.println();
      degree_str = "";
    }
    else if(next_byte >= '0' || next_byte <= '9' || next_byte == '-')
    {
      degree_str.concat(char(next_byte));
      Serial3.print(next_byte);
    }
  }
}
