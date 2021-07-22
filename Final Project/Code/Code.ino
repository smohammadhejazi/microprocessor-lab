#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <TimedAction.h>

#define D4 14
#define D5 15
#define D6 16
#define D7 17
#define EN 18
#define RS 19
#define C1 22
#define C2 23
#define C3 24
#define R1 25
#define R2 26
#define R3 27
#define R4 28
#define EN1 30
#define IN1 31
#define IN2 32
#define SERVO_PMW 34
#define RST0 36
#define RST1 37
#define RST2 38
#define RST3 39
#define FL0 41
#define FL1 42
#define FL2 43
#define FL3 44
#define DOOR0 46
#define DOOR1 47
#define DOOR2 48
#define DOOR3 49
#define NUMBER_OF_FLOORS 4

const byte KEY_ROWS = 4;
const byte KEY_COLS = 3;
byte rowPins[KEY_ROWS] = {R1, R2, R3, R4};
byte colPins[KEY_COLS] = {C1, C2, C3};
char hexaKeys[KEY_ROWS][KEY_COLS] = 
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}  
};

void checkFloor();
void addToPath(int entry);
int popFromPath();
void checkKeypad();
void moveElevator();
void openDoor();
void closeDoor();
void goUp();
void goDown();
void startMoving();
void stopMoving();
void updateLCD(int f);
void turnFloorOff(int f);
void drawUpArrow();
void drawDownArrow();
int checkOutsideDoor();

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, KEY_ROWS, KEY_COLS);
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
Servo door;
TimedAction checkFloorThread = TimedAction(10, checkFloor);
TimedAction checkKeypadThread = TimedAction(10, checkKeypad);

long long unsigned timer = 0;
int path[24];
int floorArray[NUMBER_OF_FLOORS] = {0};
int pathSize = 0;
int moving = 0;
int currentFloor = 0;
int nextDest;
int pressedFloor;
int isOutsideDoorOpen = 1;
int outSideDoor;
char key;

void setup() 
{
    pinMode(SERVO_PMW, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(EN1, OUTPUT);
    pinMode(RST0, OUTPUT);
    pinMode(RST1, OUTPUT);
    pinMode(RST2, OUTPUT);
    pinMode(RST3, OUTPUT);
    pinMode(FL0, INPUT);
    pinMode(FL1, INPUT);
    pinMode(FL2, INPUT);
    pinMode(FL3, INPUT);
    pinMode(DOOR0, INPUT);
    pinMode(DOOR1, INPUT);
    pinMode(DOOR2, INPUT);
    pinMode(DOOR3, INPUT);
   
    Serial.begin(9600);
    door.attach(SERVO_PMW);
    lcd.begin(16, 4);
    updateLCD(currentFloor);
    delay(1000);
}

void loop() 
{
    checkFloorThread.check();
    checkKeypadThread.check();
    if (checkOutsideDoor() == 0)
    {
        moveElevator();
        sleep(500);
    }
}

//The elevator moving sequence
void moveElevator()
{
    if (pathSize > 0)
    {
        nextDest = popFromPath();
        moving = 1;
        sleep(1000);
        closeDoor();
        sleep(500);
        startMoving();
        stopMoving();
        sleep(500);
        openDoor();
        moving = 0;
        turnFloorOff(currentFloor);
    }
}

//Start moving the elevator
void startMoving()
{
    Serial.println("Starting to Moving");
    while (1)
    {
        checkFloorThread.check();
        checkKeypadThread.check();

        sleep(1000);
        //If the destenation is higher, go up and down otherwise
        //also if we reach destenation, stop
        if (nextDest > currentFloor)
        {
            currentFloor++;
            goUp();
            updateLCD(currentFloor);
            drawUpArrow();
        }
        else if (nextDest < currentFloor)
        {
            currentFloor--;
            goDown();
            updateLCD(currentFloor);
            drawDownArrow();
        }
        else
        {
            updateLCD(currentFloor);
            return;
        }
    }
}

//Check if any keys are pressed inside the elevator panel
void checkKeypad()
{
    key = keypad.getKey();
    if (key != NO_KEY)
    {
        if (key >= '0' && key - '0' <= NUMBER_OF_FLOORS)
        {
            if ((moving == 0 && key - '0' == currentFloor) || (moving == 1 && key - '0' == nextDest))
                ;
            else
                addToPath(key - '0');
        }
    }
}

//Check if any buttons are pressed in any of the floors
void checkFloor()
{
    for (int i = 0; i < NUMBER_OF_FLOORS; i++)
    { 
        pressedFloor = digitalRead(i + FL0);
        if (pressedFloor == HIGH && floorArray[i] == 0)
        {
            if (moving == 0 && i == currentFloor)
            {
                turnFloorOff(i);
            }
            else
            {
                floorArray[i] = 1;
                addToPath(i);
            }
        }
    }
}

//Checking if any of the outside doors are open
int checkOutsideDoor()
{
    for (int i = 0; i < NUMBER_OF_FLOORS; i++)
    {
        checkFloorThread.check();
        checkKeypadThread.check();        
        outSideDoor = digitalRead(i + DOOR0);
        if (outSideDoor == 1)
        {
            return 1;
        }
    }

    return 0;
}

void openDoor()
{
    Serial.println("Opening door");
    door.writeMicroseconds(1500);
}

void closeDoor()
{
    Serial.println("Closing door");
    door.writeMicroseconds(2000);
}

//Start motor in up direction
void goUp()
{
    Serial.println("Going up");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(EN1, HIGH);
}

//Start motor in down direction
void goDown()
{
    Serial.println("Going down");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(EN1, HIGH);
}

//Draws an up arrow on LCD
void drawUpArrow()
{
    lcd.setCursor(13, 0);
    lcd.print("*");
    lcd.setCursor(13, 1);
    lcd.print("*");
    lcd.setCursor(12, 1);
    lcd.print("*");
    lcd.setCursor(14, 1);
    lcd.print("*");
    lcd.setCursor(13, 2);
    lcd.print("*");
    lcd.setCursor(13, 3);
    lcd.print("*");
}

//Draws an down arrow on LCD
void drawDownArrow()
{
    lcd.setCursor(13, 0);
    lcd.print("*");
    lcd.setCursor(13, 1);
    lcd.print("*");
    lcd.setCursor(13, 2);
    lcd.print("*");
    lcd.setCursor(12, 2);
    lcd.print("*");
    lcd.setCursor(14, 2);
    lcd.print("*");
    lcd.setCursor(13, 3);
    lcd.print("*");
}

//Turn off the motor
void stopMoving()
{
    Serial.println("Stopped moving");
    digitalWrite(EN1, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

void updateLCD(int f)
{
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Current");
    lcd.setCursor(0, 2);
    lcd.print("Floor: ");
    lcd.print(f);
}

//Turn off the button LED in floor
void turnFloorOff(int f)
{
    digitalWrite(RST0 + f, HIGH);
    sleep(1);
    digitalWrite(RST0 + f, LOW);
    floorArray[f] = 0;
}

//Add a destination to the path array, we dont need to check
//for threads in this method because this method runs in those
//threads itself
void addToPath(int entry)
{
    for (int i = 0; i < pathSize; i++)
    {
        if (entry == path[i])
            return;
    }
    path[pathSize] = entry;
    pathSize++;
}

//Pop the las entry in path array
int popFromPath()
{
    if (pathSize <= 0)
    {
        return -1;
    }

    pathSize--;
    return path[pathSize];
}

//A function to make delay and not block the checkFloor() and
//checkKeypad() threads
void sleep(int t)
{
    timer = millis();
    while (millis() - timer < t)
    {
        checkFloorThread.check();
        checkKeypadThread.check();
    }
}
