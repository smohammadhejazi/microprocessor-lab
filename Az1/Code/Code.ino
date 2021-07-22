#define DELAY 300
#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6

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
  if (digitalRead(10) == LOW)
  {
    delay(DELAY);
    digitalWrite(LED0, HIGH);
    delay(DELAY);
    digitalWrite(LED1, HIGH);
    delay(DELAY);
    digitalWrite(LED2, HIGH);
    delay(DELAY);
    digitalWrite(LED3, HIGH);
    delay(DELAY);
    digitalWrite(LED4, HIGH);
    delay(DELAY);
    digitalWrite(LED5, HIGH);
    delay(DELAY);
    digitalWrite(LED6, HIGH); 
  }
  else if (digitalRead(11) == LOW)
  {
    delay(DELAY);
    digitalWrite(LED6, HIGH);
    delay(DELAY);
    digitalWrite(LED5, HIGH);
    delay(DELAY);
    digitalWrite(LED4, HIGH);
    delay(DELAY);
    digitalWrite(LED3, HIGH);
    delay(DELAY);
    digitalWrite(LED2, HIGH);
    delay(DELAY);
    digitalWrite(LED1, HIGH);
    delay(DELAY);
    digitalWrite(LED0, HIGH);   
  }
  else if (digitalRead(12) == LOW)
  {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);    
  }
  else
  {
    //If multiple switches are on, or all of them are off
    //Do nothing
  }
}
