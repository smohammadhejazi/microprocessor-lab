#include <Keypad.h>
#include "pitches.h"
#include "theme1.h"
#include "theme2.h"
#include "theme3.h"
#define PIN 8
#define ANALOG 0

const byte KEY_ROWS = 4;
const byte KEY_COLS = 4;
byte rowPins[KEY_ROWS] = {22, 23, 24, 25};
byte colPins[KEY_COLS] = {26, 27, 28, 29};
char hexaKeys[KEY_ROWS][KEY_COLS] = 
{
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}  
};

int melody[] = {
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, 
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4,  NOTE_E4,
  NOTE_E4, 0, NOTE_D4, NOTE_D4, 

  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, 
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4,  NOTE_E4,
  NOTE_D4, 0, NOTE_C4, NOTE_C4, 

  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_D4
};

int noteDurations[] = {
  2, 2, 2, 2, 
  2, 2, 2, 2,
  2, 2, 2, 2,
  4/3, 2, 4, 1, 

  2, 2, 2, 2, 
  2, 2, 2, 2,
  2, 2, 2, 2,
  4/3, 2, 4, 1, 

  2, 2, 2, 2, 
  2, 2, 2, 2, 2,
  2, 2, 2, 2, 2,
  2, 2
};


Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, KEY_ROWS, KEY_COLS);
int pot;
char key;

void setup() 
{
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.read() != -1)
  { 
    pot = analogRead(ANALOG);
    pot = map(pot, 0, 1023, 0, 7);
    tone(PIN, 500 * (pot + 1), 100);
  }
    
  key = keypad.getKey();
  if (key != NO_KEY)
  {
    if (key == '1') 
    {
      playSong(melody1, noteDurations1, sizeof(melody1)/sizeof(melody1[0]));
      
    }
    else if (key == '2')
    {
      playSong(melody2, noteDurations2, sizeof(melody2)/sizeof(melody2[0]));
    }
    else if (key == '3')
    {
      playSong(melody2, noteDurations3, sizeof(melody3)/sizeof(melody3[0]));
    }
    else if (key == '4')
    {
      playSong(melody, noteDurations3, sizeof(melody)/sizeof(melody[0]));
    }
  }
}

void playSong(int melody[], int noteDurations[], int n)
{
  int noteDuration;
  for (int i = 0; i < n; i++)
  {
    noteDuration = 1000 / noteDurations[i];
    pot = analogRead(ANALOG);
    pot = map(pot, 0, 1023, 0, 7);
    tone(PIN, melody[i] * pot, noteDuration);
    delay(noteDuration);
  }
}
