#include <PLab_ZumoMotors.h>

#define leftPin 2
#define middlePin 3
#define rightPin 4
#define spinPin 5
boolean rightState;
boolean leftState;
boolean middleState;
boolean turnState;
PLab_ZumoMotors PLab_motors;

void setup()
{
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(middlePin, INPUT);
  pinMode(spinPin, INPUT);

}

void loop()   // Draw a triangle. 45, 90, 45 degrees...
{
int zumoSpeed = 150;  // Speed is 200 for all operations in this example
rightState = digitalRead(rightPin);
leftState = digitalRead(leftPin);
middleState = digitalRead(middlePin);
turnState = digitalRead(spinPin);
if (rightState == HIGH){
//Turn rigth
PLab_motors.turnRight(zumoSpeed,45);
}
else if (leftState == HIGH){
//Turn rigth
PLab_motors.turnLeft(zumoSpeed,45);
}
else if (middleState == HIGH){
//Turn rigth
PLab_motors.forward(zumoSpeed,45);
}
else if (turnState == HIGH){
PLab_motors.turnLeft(zumoSpeed,5);
}
}

