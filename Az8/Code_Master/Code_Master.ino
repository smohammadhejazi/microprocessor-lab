#include <SPI.h>

#define LIGHT 0
#define TMP 1
#define A2 2
#define SS1 48
#define SS2 49

int temp;
int offset;
int light;

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
  temp = analogRead(TMP);
  offset = analogRead(A2);
  light = analogRead(LIGHT);

  temp = temp - offset;
  temp /= 2;
  light = map(light, 0, 1023, 0, 100);

  digitalWrite(SS1, 0);
  digitalWrite(SS2, 1);
  SPI.transfer(highByte(temp));
  SPI.transfer(lowByte(temp));

  delay(100);

  digitalWrite(SS1, 1);
  digitalWrite(SS2, 0);
  SPI.transfer(highByte(light));
  SPI.transfer(lowByte(light));

  delay(100);
}
