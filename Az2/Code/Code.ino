#include <Keypad.h>

#define LED0 0
#define LED0 1
#define LED0 2
#define LED0 3
#define LED0 4
#define LED0 5
#define LED0 6
#define LED0 7
#define LED0 8
#define LED0 9

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = 
{
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}  
};

byte rowPins[ROWS] = {46, 47, 48, 49};
byte colPins[COLS] = {50, 51, 52, 53};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char key;
char input;
int num = 0;
int i = 0;
unsigned int startTime = 0;

void setup() 
{
  Serial3.begin(9600);

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() 
{
  //read from terminal
  input = Serial3.read();
  
  if (input >= '0' && input <= '9')
  {
    num *= 10;
    num += (input - '0');
  }
  else if (input == 13)
  {
    //if invalid, print Invalid
    if (num < 0 || num > 9)
    {
      Serial3.println("Invalid number");
    }
    //and if valid, turn on LEDS
    else
    {
      //Turn off all LEDs
      i = 0;
      while(i < 9)
      {
        digitalWrite(i, LOW);
        i++;
      }
    
      //Turn on LEDs
      i = 0;
      while (i < num)
      {
        delay(200);
        digitalWrite(8 - i, HIGH);
        i++;
      }
    }
    num = 0;
  }

  //read from keypad
  key = keypad.getKey();
  //check for keypad input, if there isn't any, skip
  if (key != NO_KEY)
  {
    Serial3.println(key);
    if (key >= '0' && key <= '9')
    {
      //Turn LEDs off
      i = 0;
      while (i < 9)
      {
        digitalWrite(i, LOW);
        i++;
      }

      //Turn LEDs on
      i = 0;
      while (i < (key - '0'))
      {
        delay(200);
        digitalWrite(8 - i, HIGH);
        i++;
      }
    }
  }
  
}
