#include <PLab_ZumoMotors.h>
#include <pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>


// Tweak these to change speed of the Sumo
#define REVERSE_SPEED 400
#define TURN_SPEED 400
#define FORWARD_SPEED 400
#define REVERSE_DURATION 400
#define TURN_DURATION 150


//Activates the integrated button on the Sumo. Uses pin 12.
Pushbutton button(ZUMO_BUTTON); 

//Configures the array of IR-sensors underneath. There are 6 sensors.
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

//These pins receive input from Arduino-Helper
#define leftPin 2
#define middlePin 3
#define rightPin 0
#define spinPin 6
boolean rightState;
boolean leftState;
boolean middleState;
boolean turnState;

PLab_ZumoMotors PLab_motors;
ZumoReflectanceSensorArray sensors;

int zumoSpeed = 150; // Speed is 150 by default. This is not very much used in the code.


void setup(){
  Serial.begin(9600);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(middlePin, INPUT);
  pinMode(spinPin, INPUT);
  
  //Click the button once to initialize IR-sensors.
  button.waitForButton();
  sensors.init();
  
  
  //Hvorfor er denne her?
  delay(500);
  
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  
  //Calibrates for 10 seconds. 
  unsigned long startTime = millis();
  while(millis()-startTime < 10000){
    sensors.calibrate();
  }
  digitalWrite(13,LOW);
  
  //Press the button again to start wrestling.
  button.waitForButton();
}


void loop(){
  //Checks for input from the Arduino-helper
  rightState = digitalRead(rightPin);
  leftState = digitalRead(leftPin);
  middleState = digitalRead(middlePin);
  turnState = digitalRead(spinPin);
   
   
  //Checks for signals from the SumoHelper to determine what to do.
  
  //If the Sumohelper doesn't detect anything, start searching to the left.
  //This should be changed to make the Sumo turn the way the other robot was last seen.
  
  if (turnState == HIGH){
      PLab_motors.turnLeft(zumoSpeed,10); //Turns 10 degrees to the left.
  }
  
  else if (middleState == HIGH){ //Drives forward 25 cm
      goForward(25);
  }
  
  else if (rightState == HIGH){ 
      PLab_motors.turnRight(zumoSpeed,25); //Turn 25 degrees right, then drives forward 25 cm
      goForward(25);
  }
  
  else if (leftState == HIGH){ 
      PLab_motors.turnLeft(zumoSpeed,25);  //Turn 25 degrees left, then drives forward 25 cm
      goForward(25);
  }
}
  
void goForward(int cm){
    //This for-loop moves 1 cm at a time, and checks the floor for black tape.
    for(int i = 0; i < cm; i++){
        PLab_motors.forward(200,1); //Moves forward. Burde denne endres til max fart? Ja, ellers dytter den ikke med all kraft.
        sensors.readLine(sensor_values);
        
        if (sensor_values[0] == 1000) //Checks if there is a line on the left side.
        {
            PLab_motors.turnRight(400,130); //Turns 130 degrees to the right with full speed.
        }
        
        else if (sensor_values[5] == 1000) //Checks if there is a line on the right side.
        {
            PLab_motors.turnLeft(400,130); //Turns 130 degrees to the left with full speed.
        }
        else if (sensor_values[1] > 900 && //Checks if the robot has driven straight onto the line.
                 sensor_values[2] > 900 && //This code will probably never be executed :(
                 sensor_values[3] > 900 && 
                 sensor_values[4] > 900)
        {
            PLab_motors.turnLeft(400, 180); //Turns around 180 degrees with full speed.
        }
    }
}
