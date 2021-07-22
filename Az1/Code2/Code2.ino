#define DELAY 300
#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6

int i = 0;
int j = 0;

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
}

void loop() {
  if (digitalRead(12) == LOW)
  {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);    

    i = 0;
    j = 0;
  }
  else
  {
    if (digitalRead(10) == LOW)
    {
      switch (i)
      {
        case 0:
          digitalWrite(LED0, HIGH);
          break;
        case 1:
          digitalWrite(LED1, HIGH);
          break;
        case 2:
          digitalWrite(LED2, HIGH);
          break;
        case 3:
          digitalWrite(LED3, HIGH);
          break;
        case 4:
          digitalWrite(LED4, HIGH);
          break;
        case 5:
          digitalWrite(LED5, HIGH);
          break;
        case 6:
          digitalWrite(LED6, HIGH);  
          break;  
      }
      i++;
    }
    if (digitalRead(11) == LOW)
    {
      switch (j)
      {
        case 0:
          digitalWrite(LED6, HIGH);
          break;
        case 1:
          digitalWrite(LED5, HIGH);
          break;
        case 2:
          digitalWrite(LED4, HIGH);
          break;
        case 3:
          digitalWrite(LED3, HIGH);
          break;
        case 4:
          digitalWrite(LED2, HIGH);
          break;
        case 5:
          digitalWrite(LED1, HIGH);
          break;
        case 6:
          digitalWrite(LED0, HIGH);  
          break;  
      }
      j++;
    }
    delay(500);
  }
}
