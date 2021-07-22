const int pin = 34;

void setup() 
{
  pinMode(pin, OUTPUT);
}

void loop() 
{
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}
