#include <SPI.h>

#define SS1 48
#define SS2 49

char myName[] = "Hello Mohammad  ";
char stdNumber[] = "9733020         ";

void setup() 
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS1, 1);
  digitalWrite(SS2, 1);
}

void loop() 
{
  digitalWrite(SS1, 0);
  digitalWrite(SS2, 1);
  for (int i = 0; i < 16; i++)
  {
    SPI.transfer(myName[i]);
  }
  
  delay(100);

  digitalWrite(SS1, 1);
  digitalWrite(SS2, 0);
  for (int i = 0; i < 16; i++)
  {
    SPI.transfer(stdNumber[i]);
  }
  
  delay(100);
}
