#include<SPI.h>
#include <LiquidCrystal.h>

const int rs = 27, en = 26, d4 = 22, d5 = 23, d6 = 24, d7 = 25;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

volatile int i = 0;
byte myArray[2];

void setup()
{
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();  //allows SPI interrupt
}

void loop(void)
{
  if (i == 2)
  {
    int x = myArray[0]<<8|myArray[1];
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(x);
    i=0;
  }
}

ISR (SPI_STC_vect)   //Inerrrput routine function
{
  myArray[i] = SPDR;
  i++;
}
