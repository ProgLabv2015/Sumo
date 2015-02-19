#include <PLab_ZumoMotors.h>
#include <pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>


// tune these
#define REVERSE_SPEED 400
#define TURN_SPEED 400
#define FORWARD_SPEED 400
#define REVERSE_DURATION 400
#define TURN_DURATION 150

Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

//Configures the array of IR-sensors underneath
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

//These pins recieve input from Arduino-Helper
#define leftPin 2
#define middlePin 3
#define rightPin 6
#define spinPin 0
boolean rightState;
boolean leftState;
boolean middleState;
boolean turnState;

PLab_ZumoMotors PLab_motors;
ZumoMotors motors;
ZumoReflectanceSensorArray sensors;

int zumoSpeed = 150; // Speed is 200 for all operations in this example


void setup(){
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(middlePin, INPUT);
  pinMode(spinPin, INPUT);
  
  //sensors.init();
  button.waitForButton();
  
  Serial.begin(9600);
  sensors.init();
  
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  unsigned long startTime = millis();
  while(millis()-startTime < 10000){
    sensors.calibrate();
  }
  digitalWrite(13,LOW);
  button.waitForButton();
}


void loop(){
  //Checks for input from the Arduino-helper
  rightState = digitalRead(rightPin);
  leftState = digitalRead(leftPin);
  middleState = digitalRead(middlePin);
  turnState = digitalRead(spinPin);
   
  if (turnState == HIGH){ //Checks if there is no detection.
  //Turns left if there isn't
  PLab_motors.turnLeft(zumoSpeed,10);
  }
  else if (middleState == HIGH){ //Drive forward,
  goForward(25);
  }
  
  else if (rightState == HIGH){ //Turn right
  PLab_motors.turnRight(zumoSpeed,25);
  goForward(25);
  }
  
  else if (leftState == HIGH){ //Turn left
  PLab_motors.turnLeft(zumoSpeed,25);
  goForward(25);
  }


  }
  
  void goForward(int cm){
  for(int i = 0; i<cm;i++){
  PLab_motors.forward(400,1);
  //Insert code to read sensors here
  sensors.readLine(sensor_values);
  if (sensor_values[0] == 1000)
  {
  PLab_motors.turnRight(400,130);
  PLab_motors.forward(400,10);
  }
  else if (sensor_values[5] == 1000)
  {
  PLab_motors.turnLeft(zumoSpeed,130);
  PLab_motors.forward(400,10);
  }

}
}
