#include <NewPing.h>

//The pins where the sonars are connected
#define echoPin0 2
#define trigPin0 3

#define echoPin1 4
#define trigPin1 5

#define echoPin2 6
#define trigPin2 7


//Pins that give signals to the Sumo
#define leftPin 8
#define midPin 9
#define rightPin 10
#define spinPin 11

//Tweak this to change sensitivity of sensors. The number is threshold of sensors in cm
#define MAX_DISTANCE 70


NewPing sonar0(trigPin0,echoPin0,MAX_DISTANCE);
NewPing sonar1(trigPin1,echoPin1,MAX_DISTANCE);
NewPing sonar2(trigPin2,echoPin2,MAX_DISTANCE);


long dist0;
long dist1;
long dist2;


void setup(){
  
  
      //Initializes the pins to the Sumo
      pinMode(leftPin, OUTPUT);
      pinMode(rightPin, OUTPUT);
      pinMode(midPin, OUTPUT);
      pinMode(spinPin, OUTPUT);
      digitalWrite(leftPin, LOW);
      digitalWrite(rightPin, LOW);
      digitalWrite(midPin, LOW);
      digitalWrite(spinPin, LOW);
      
      //Initializes the pins to the sonars
      pinMode(trigPin0, OUTPUT);
      pinMode(trigPin1, OUTPUT);
      pinMode(trigPin2, OUTPUT);
      pinMode(echoPin0, INPUT);
      pinMode(echoPin1, INPUT);
      pinMode(echoPin2, INPUT);
      digitalWrite(trigPin0, LOW); 
      digitalWrite(trigPin1, LOW);
      digitalWrite(trigPin2, LOW);
}
void loop(){
      //Updates values with a new ping from sonars. Sonars can ping about 30 times every second.
      dist0 = sonar0.ping_cm();
      dist1 = sonar1.ping_cm();
      dist2 = sonar2.ping_cm();
      
      if (dist0 > 0 && dist0 < MAX_DISTANCE){
            digitalWrite(spinPin, LOW);
            digitalWrite(leftPin, HIGH);
            digitalWrite(rightPin, LOW);
            digitalWrite(midPin, LOW);
            //Serial.println("LEFT");
      }
      
      else if(dist1 > 0 && dist1 < MAX_DISTANCE){
            digitalWrite(spinPin, LOW);
            digitalWrite(midPin, HIGH);
            digitalWrite(leftPin, LOW);
            digitalWrite(rightPin, LOW);
            //Serial.println("STRAIGHT FORWARD");
      }
      
      else if(dist2 > 0 && dist2 < MAX_DISTANCE){
            digitalWrite(spinPin, LOW);
            digitalWrite(rightPin, HIGH);
            digitalWrite(midPin, LOW);
            digitalWrite(leftPin, LOW);
            //Serial.println("RIGHT");
      }
      
      else {
            digitalWrite(spinPin, HIGH);
            digitalWrite(leftPin, LOW);
            digitalWrite(rightPin, LOW);
            digitalWrite(midPin, LOW);
      } 
      
      
}
