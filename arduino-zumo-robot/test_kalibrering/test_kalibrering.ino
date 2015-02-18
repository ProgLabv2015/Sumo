
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

ZumoReflectanceSensorArray sensors;

#define NUM_SENSORS 6
unsigned int sensorValues[NUM_SENSORS];

void setup(){
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
}

void loop(){
  unsigned int position = sensors.readLine(sensorValues);
  for(byte i = 0; i < NUM_SENSORS; i++){
    Serial.print(sensorValues[i]);
    Serial.print(' ');
  }
  Serial.print("    ");
  Serial.println(position);
  
  delay(250);
  
}
