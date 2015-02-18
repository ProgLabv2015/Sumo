
int speakerOut = 9;
int micInput = A0;
int micValue = 0;
int frequency = 880;
const int toneLength = 500;
int count = 0;
int time = 0;
void setup() {
  pinMode(speakerOut, OUTPUT);
  pinMode(micInput, INPUT);
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
    tone(speakerOut, frequency, 2000);
    delay(6000);
  }
  count=0;
  time =0;
}

