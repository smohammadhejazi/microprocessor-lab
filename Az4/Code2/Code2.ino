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

char key;
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
  key = keypad.getKey();
  if (key != NO_KEY)
  {
    if (key == '=')
    {
      degree_int = degree_str.toInt();
      if (degree_int >= 0 && degree_int <= 180)
      {
        value = map(degree_int, 0, 180, 1500, 2000);
      }
      else if (degree_int >= 180 && degree_int <= 360)
      {
        value = map(degree_int - 360, -180, 0, 1000, 1500);
      }
      Serial3.println();
      motor.writeMicroseconds(value);
      degree_str = "";
    }
    else if(key >= '0' || key <= '9')
    {
      degree_str.concat(key);
      Serial3.print(key);
    }
  }
}
