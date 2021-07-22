#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("A");
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A");
  for (int i = 0; i < 16; i++)
  {
    delay(100);
    lcd.scrollDisplayRight();
    
  }
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("A");
  for (int i = 0; i < 16; i++)
  {
    delay(100);
    lcd.scrollDisplayRight();
  }
}
