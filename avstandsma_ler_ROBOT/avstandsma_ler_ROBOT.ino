#include <NewPing.h>


#define echoPin0 2
#define trigPin0 3
#define echoPin1 4
#define trigPin1 5
#define echoPin2 6
#define trigPin2 7
#define leftPin 8
#define midPin 9
#define rightPin 10
#define spinPin 11
#define MAX_DISTANCE 150


NewPing sonar0(trigPin0,echoPin0,MAX_DISTANCE);
NewPing sonar1(trigPin1,echoPin1,MAX_DISTANCE);
NewPing sonar2(trigPin2,echoPin2,MAX_DISTANCE);

long dist0;
long dist1;
long dist2;


void setup(){
  Serial.begin(9600);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(midPin, OUTPUT);
  pinMode(spinPin, OUTPUT);
  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);
  digitalWrite(midPin, LOW);
  digitalWrite(spinPin, LOW);
  /*pinMode(trigPin0, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin0, LOW); 
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);*/
  
}

void loop(){
  dist0 = sonar0.ping_cm();
  dist1 = sonar1.ping_cm();
  dist2 = sonar2.ping_cm();
  
  
  
  
  Serial.print("Distance0: ");
  Serial.print(dist0);
  Serial.println(" cm");
  Serial.print("Distance1: ");
  Serial.print(dist1);
  Serial.println(" cm");
  Serial.print("Distance2: ");
  Serial.print(dist2);
  Serial.println(" cm");
  Serial.println("------------");
  delay(500);
  
  if (dist0 > 0 && dist0 < 40){
    digitalWrite(spinPin, LOW);
    digitalWrite(leftPin, HIGH);
    Serial.println("LEFT");
  }
  else if(dist1 > 0 && dist1 < 40){
    digitalWrite(spinPin, LOW);
    digitalWrite(midPin, HIGH);
    Serial.println("STRAIGHT FORWARD");
  }
  else if(dist2 > 0 && dist2 < 40){
    digitalWrite(spinPin, LOW);
    digitalWrite(rightPin, HIGH);
    Serial.println("RIGHT");
  }
  else {
    digitalWrite(spinPin, LOW);
    digitalWrite(spinPin, HIGH);
  }    
  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);
  digitalWrite(midPin, LOW);
} 
