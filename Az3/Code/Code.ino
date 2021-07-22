#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
const char myName[] = "        Mohammad                ";
int start = 9;
int stringIndex;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Mohammad");
}

void loop() {

  delay(200);
  
  lcd.setCursor(0, 0);
  stringIndex = start;
  for(int i = 0; i < 16; i++)
  {
    if (stringIndex >= 32)
      stringIndex %= 32;
    lcd.print(myName[stringIndex]);
    stringIndex++;
  }
  lcd.setCursor(0, 1);
  stringIndex = start + 16;
  for(int i = 0; i < 16; i++)
  {
    if (stringIndex >= 32)
      stringIndex %= 32;
    lcd.print(myName[stringIndex]);
    stringIndex++;
  }

  start++;
  if(start >= 32)
    start = 0;
}
