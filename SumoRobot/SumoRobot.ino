#include <PLab_ZumoMotors.h>
#include <pushbutton.h>
#include <QTRSensors.h> //Needed for the sensor array
#include <ZumoReflectanceSensorArray.h>

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


Pushbutton button(ZUMO_BUTTON); //Activates the integrated button on the Sumo. Uses pin 12.
PLab_ZumoMotors PLab_motors;
ZumoReflectanceSensorArray sensors;

int zumoSpeed = 150; // Speed is 150 by default. This is not very much used in the code.

char lastSeenDirection = 'l';


void setup(){
    Serial.begin(9600);
    pinMode(leftPin, INPUT);
    pinMode(rightPin, INPUT);
    pinMode(middlePin, INPUT);
    pinMode(spinPin, INPUT);
    
    //Click the button once to initialize IR-sensors.
    button.waitForButton();
    sensors.init();
    
    
    //Waits a half second before starting to calibrate the IR-sensors
    delay(500);
    
    //Turns on the yellow LED to show that we are calibrating.
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    
    
    //Calibrates for 10 seconds. 
    unsigned long startTime = millis();
    while(millis()-startTime < 10000){
        PLab_motors.turnRight(200,20);
        sensors.calibrate();
    }
    digitalWrite(13,LOW); //Turns off the yellow LED.
    
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
    //The sumo turns the way the enemy was last seen. Default is left.
    if (turnState == HIGH){
        if(lastSeenDirection == 'r'){ //If the enemy was last seen on the right, turn right.
            PLab_motors.turnRight(zumoSpeed,10); //Turns 10 degrees to the left.
        }
        
        else{ //Else, turn left.
            PLab_motors.turnLeft(zumoSpeed,10); //Turns 10 degrees to the left.
        }
    }
    
    else if (middleState == HIGH){ //Drives forward 25 cm
        goForward(10);
    }
    
    else if (rightState == HIGH){ 
        lastSeenDirection = 'r';
        PLab_motors.turnRight(zumoSpeed,25); //Turn 25 degrees right, then drives forward 25 cm
        goForward(10);
    }
    
    else if (leftState == HIGH){ 
        lastSeenDirection = 'l';
        PLab_motors.turnLeft(zumoSpeed,25);  //Turn 25 degrees left, then drives forward 25 cm
        goForward(10);
    }
}
  
void goForward(int cm){
    //This for-loop moves 1 cm at a time, and checks the floor for black tape.
    for(int i = 0; i < cm; i++){
        PLab_motors.forward(200,1); //Moves forward at full speed.
        sensors.readCalibrated(sensor_values);
        
        if (sensor_values[0] == 1000) //Checks if there is a line on the left side. Burde verdien være 1000 her?
        {
            lastSeenDirection = 'r';
            PLab_motors.turnRight(400,130); //Turns 130 degrees to the right with full speed.
            goForward(10);
            
        }
        
        else if (sensor_values[5] == 1000) //Checks if there is a line on the right side. Burde verdien være 1000 her?
        {
            lastSeenDirection = 'r';
            PLab_motors.turnLeft(400,130); //Turns 130 degrees to the left with full speed.
            goForward(10);
        }
        else if (sensor_values[1] > 900 && //Checks if the robot has driven straight onto the line.
                 sensor_values[2] > 900 && //This code will probably never be executed :(
                 sensor_values[3] > 900 && 
                 sensor_values[4] > 900)
        {
            PLab_motors.turnLeft(400, 180); //Turns around 180 degrees with full speed.
            goForward(10);
        }
    }
}
