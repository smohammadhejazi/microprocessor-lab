#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

char key;
String number = "";
String op1 = "", op2 = "", sign = "";
String result;
bool finished = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {

  key = keypad.getKey();

  if (key != NO_KEY)
  {
    if (finished)
    {
      lcd.clear();
      finished = false;
    }

    if(key == 'C')
    {
      lcd.clear();
      finished = false;
      op1 = "";
      op2 = "";
      sign = "";
      result = "";
      number = "";
      lcd.setCursor(0, 0);
    }
    else if (key == '=')
    { 
      result = "";
      if (op1 == "" && op2 == "")
      {
        result = "0";
      }
      else if (op1 != "" && op2 == "")
      {
        result = op1;
      }
      else if(op1 == "" && op2 != "")
      {
        result = op2;
      }
      else
      {
        if (sign == "+")
        {
          result.concat(op1.toInt() + op2.toInt());
        }
        else if (sign == "-")
        {
          result.concat(op1.toInt() - op2.toInt());
        }
        else if (sign == "*")
        {
          result.concat(op1.toInt() * op2.toInt());
        }
        else if (sign == "/")
        {
          if (op2 == "0")
              result = "Invalid";
            else
              result.concat(op1.toInt() / op2.toInt());
        }
      }
      
      finished = true;
      lcd.setCursor(0, 1);
      lcd.print(result);
      lcd.setCursor(0, 0);

      op1 = "";
      op2 = "";
      sign = "";
      result = "";
      number = "";
    }
    else if (key == '+' || key == '-' || key == '*' || key == '/')
    {
      number = "";
      sign = key;
      if (op1 == "")
      {
        op1 = "0";
        lcd.print(0);
        lcd.print(sign);
      }
      else
      {
        lcd.print(key);
      }
    }
    else
    {
      lcd.print(key);
      number.concat(key);
      if (sign == "")
        op1 = number;
      else
        op2 = number;
    }
  }
}
