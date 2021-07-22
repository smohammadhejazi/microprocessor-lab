#include<SPI.h>
#include <LiquidCrystal.h>

const int rs = 27, en = 26, d4 = 22, d5 = 23, d6 = 24, d7 = 25;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

volatile int i = 0;
byte myArray[16];

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
  if (i == 16)
  {
    lcd.setCursor(0, 0);
    for (int j = 0; j < 16; j++)
    {
      lcd.print((char)myArray[j]);
    }

    i=0;
  }
}

ISR (SPI_STC_vect)   //Inerrrput routine function
{
  myArray[i] = SPDR;
  i++;
}
