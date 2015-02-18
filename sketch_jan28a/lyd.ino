
const int soundPin = 8;
const int toneLength = 500;

void setup(){
}

void loop(){
  tone(soundPin, 440, toneLength);
  delay(toneLength);
  delay(toneLength);
  
  tone(soundPin, 1000, toneLength);
  delay(toneLength);
  
  tone(soundPin, 2000, toneLength);
  delay(toneLength);
  
  tone(soundPin, 2500, toneLength);
  delay(toneLength);
}

