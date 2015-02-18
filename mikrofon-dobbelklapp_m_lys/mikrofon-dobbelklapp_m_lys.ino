
int speakerOut = 9;
int micInput = A0;
int micValue = 0;
int frequency = 880;
const int ledPin = 13;
const int ledPin1 = 12;
const int ledPin2 = 11;
const int toneLength = 500;
int count = 0;
int time = 0;
int lys = 0;
void setup() {
  pinMode(speakerOut, OUTPUT);
  pinMode(micInput, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  Serial.begin(9600);
}

void loop() {
  micValue = analogRead(micInput);
  if (micValue >1000){
    //Serial.println(micValue);
    count += 1;
    delay(200);
    while((time < 1000)&&(count<2)){
      micValue = analogRead(micInput);
      Serial.println(time);
      if (micValue > 1000){
        count += 1;
      }
      else{
        time += 10;
      }
    }
  }
  Serial.println(count);
  
  if ((count>0) && (count%2 == 0)){
    if (lys%2 == 0){
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
    }
    else{
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
    }
    //tone(speakerOut, frequency, 2000);
    lys += 1;
    delay(500);
  }
  count=0;
  time =0;
}

