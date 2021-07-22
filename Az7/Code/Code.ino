//Seyyed Mohammad Hejazi Hoseini
//1400- Spring

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

#define DEVICE_ADDRESS 0b1010000

int getTime();
void turnOnLED();
void workLoop(int* time_s, int stopClock);
void checkStop();

const int LED1 = 30, LED2 = 31, LED3 = 32, LED4 = 33;
const int rs = 48, en = 49, d4 = 50, d5 = 51, d6 = 52, d7 = 53;
const byte KEY_ROWS = 4;
const byte KEY_COLS = 4;
char hexaKeys[KEY_ROWS][KEY_COLS] = 
{
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}  
};
byte rowPins[KEY_ROWS] = {22, 23, 24, 25};
byte colPins[KEY_COLS] = {26, 27, 28, 29};
unsigned long timer = 0;
char key;
boolean working = true;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, KEY_ROWS, KEY_COLS);

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  Wire.begin();
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
}

void loop()
{
  key = keypad.getKey();

  timer = millis();

  if (key != NO_KEY)
  {
    if (key == '/')
    {
      int time_s[4] = {2, 2, 2, 2};
      workLoop(time_s);
    }
    else if (key == '*')
    {
      int time_s[4];
      int stopClock = 0;
      Wire.beginTransmission(DEVICE_ADDRESS);
      Wire.write(0);
      Wire.write(1);
      Wire.endTransmission();

      Wire.requestFrom(DEVICE_ADDRESS, 4);

      for (int i = 0; i < 4; i++)
      {
        time_s[i] = Wire.read();
      }

      Serial.println("Reading: ");
      Serial.println(time_s[0]);
      Serial.println(time_s[1]);
      Serial.println(time_s[2]);
      Serial.println(time_s[3]);

      workLoop(time_s);
    }
    else if (key == '+')
    {
      int time_s[4];

      for (int i = 1; i <= 4; i++)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Phase ");
        lcd.print(i);
        lcd.print(" time:");
        time_s[i-1] = getTime();
      }
      Serial.println("Writing: ");
      Serial.println(time_s[0]);
      Serial.println(time_s[1]);
      Serial.println(time_s[2]);
      Serial.println(time_s[3]);
      Wire.beginTransmission(DEVICE_ADDRESS);
      //Memmory address
      Wire.write(0);
      Wire.write(1);
      //Data
      for (int i = 0; i < 4; i++)
      {
        if (time_s[i] >= 256)
        {
          Wire.write(255);
        }
        else
        {
          Wire.write(time_s[i]);
        }
      }
      Wire.endTransmission();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Setting:");
      lcd.setCursor(0, 1);
      lcd.print("Completed");  
    }
  }
}

/**
 * Work loop function, the input is the phases time
 * array, then we us the array to make the stop clock.
 */
void workLoop(int* time_s)
{
  int phase = 1;
  int phaseTimer = 0;
  int stopClock = time_s[0] + time_s[1] + time_s[2] + time_s[3];

  if (stopClock <= 0)
  {
    return;
  }
  
  while(stopClock >= 0)
  {
    if (phase > 4)
    {
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Time Left: 0");
      lcd.setCursor(0, 1); 
      lcd.print("Phase: Completed");
      turnOnLED(0);
      break;
    }    
     
    if (time_s[phase - 1] <= phaseTimer)
    {
      phaseTimer = 0;
      phase++;
      continue;
    }

    turnOnLED(phase);
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Time Left: ");
    lcd.print(stopClock);
    lcd.setCursor(0, 1); 
    lcd.print("Phase: ");
    lcd.print(phase);
    
    checkStop();
    phaseTimer++;
    stopClock--; 
  }
}

/**
 * Function to turn on LEDs based on the
 * phase that program is currently in. Phase 0
 * is the ending.
 */
void turnOnLED(int led)
{
  if (led == 0)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (led >= 1 && led <= 4)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(led - 1 + LED1, HIGH);
  }
}

/*
 * A function to get the phase times from
 * keypad when you are in settings ('+' mode), 
 * if you press '=', the final number is returned
 */
int getTime()
{
  int time_s = 0;
  lcd.setCursor(0, 1);
  while(true)
  {
    key = keypad.getKey();

    if (key >= '0' && key <= '9')
    {
      lcd.print(key);
      time_s = (time_s * 10) + (key - '0');
    }
    else if (key == '=')
    {
      return time_s;
    }
  }
}


/* Delayin function with ability to stop by
 * pressing the 'C' button
 */
void checkStop()
{
  timer = millis();
  while (millis() - timer < 999)
  {
    key = keypad.getKey();
  
    if (key == 'C')
    {
      working = !working;
    }

    if (working == false)
    {
      timer = millis();
    }
  }
}
