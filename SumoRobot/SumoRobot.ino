#include <PLab_ZumoMotors.h>
#include <pushbutton.h>
#include <QTRSensors.h> //Needed for the sensor array
#include <ZumoReflectanceSensorArray.h>

//Configures the array of IR-sensors underneath. There are 6 sensors.
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

//These pins receive input from Arduino-Helper
#define leftPin A4
#define middlePin 3
#define rightPin 6
boolean rightState;
boolean leftState;
boolean middleState;


Pushbutton button(ZUMO_BUTTON); //Activates the integrated button on the Sumo. Uses pin 12.
PLab_ZumoMotors PLab_motors;
ZumoReflectanceSensorArray sensors;

int zumoSpeed = 350; // Speed is 150 by default. This is not very much used in the code.
int turnSpeed = 400;



void setup(){
    Serial.begin(9600);
    pinMode(leftPin, INPUT);
    pinMode(rightPin, INPUT);
    pinMode(middlePin, INPUT);
    
    //Click the button once to initialize IR-sensors.
    button.waitForButton();
    sensors.init(QTR_NO_EMITTER_PIN);
    
    
    //Waits a half second before starting to calibrate the IR-sensors
    delay(500);
    
    //Turns on the yellow LED to show that we are calibrating.
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    
    
    //Calibrates for 10 seconds. 
    unsigned long startTime = millis();
    while(millis()-startTime < 5000){
        PLab_motors.turnRight(50,10);
        sensors.calibrate();
    }
    digitalWrite(13,LOW); //Turns off the yellow LED.
    
    //Press the button again to start wrestling.
    button.waitForButton();
}   
    
    
void loop(){
  
  
    rightState = 0;
    leftState = 0;
    middleState = 0;
    //Checks for input from the Arduino-helper
    rightState = digitalRead(rightPin);
    leftState = digitalRead(leftPin);
    middleState = digitalRead(middlePin);
    
     
     /*Serial.println(rightState);
     Serial.println(leftState);
     Serial.println(middleState);*/
     
    //Checks for signals from the SumoHelper to determine what to do.
    //The sumo turns the way the enemy was last seen. Default is left.
    
    
    
    
    
    if (leftState == HIGH){ 
        Serial.println("SNU VENSTRE!");
        PLab_motors.turnLeft(turnSpeed,15);  //Turn 20 degrees left, then drives forward 25 cm
        //PLab_motors.forward(zumoSpeed,10);
    }
    
    if (rightState == HIGH){ 
        Serial.println("SNU HOYRE!");
        PLab_motors.turnRight(turnSpeed,15); //Turn 20 degrees right, 
        //PLab_motors.forward(zumoSpeed,10); // then drives forward 1 cm
    }
    
    if (middleState == HIGH){ //Drives forward 25 cm
        Serial.println("GAA FOROVER!");
        goForward(5);
    }
    //Serial.println("-------------------------");
}
  
void goForward(int cm){
    //This for-loop moves 1 cm at a time, and checks the floor for black tape.
    for(int i = 0; i < cm; i++){
        PLab_motors.forward(zumoSpeed,1); //Moves forward at full speed.
        sensors.readCalibrated(sensor_values);
        //Kan hende vi må snu om all logikken her inne, pga hvit strek...
        if (sensor_values[0] == 0) //Checks if there is a line on the left side. Burde verdien være 1000 her?
        { 
            PLab_motors.backward(zumoSpeed, 6);
            PLab_motors.turnRight(turnSpeed,130); //Turns 130 degrees to the right with full speed.
        
        }
        
        else if (sensor_values[5] == 0) //Checks if there is a line on the right side. Burde verdien være 1000 her?
        {
            PLab_motors.backward(zumoSpeed, 6);
            PLab_motors.turnLeft(turnSpeed,130); //Turns 130 degrees to the left with full speed.
           
        }
        else if (sensor_values[1] < 100 && //Checks if the robot has driven straight onto the line.
                 sensor_values[2] < 100 && //This code will probably never be executed :(
                 sensor_values[3] < 100 && 
                 sensor_values[4] < 100)
        {
            PLab_motors.backward(zumoSpeed, 6);
            PLab_motors.turnLeft(turnSpeed, 180); //Turns around 180 degrees with full speed.
            
        }
    }
}
