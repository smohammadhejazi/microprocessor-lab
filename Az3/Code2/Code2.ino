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
String password;
int n = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {

  key = keypad.getKey();

  if (key != NO_KEY)
  {
    if (key == '=')
    {
      n = 0;
      lcd.clear();
      if (password.compareTo("9733020") == 0)
      {
        lcd.print("Correct Passowrd");
      }
      else
      {
        lcd.print("Wrong Passowrd");
      }
      delay(500);
      lcd.clear();
      password = "";
    }
    else
    {
      n++;
      if (n >= 16)
        lcd.setCursor(0, 1);
      lcd.print(key);
      password.concat(key);
    }
  }
}
