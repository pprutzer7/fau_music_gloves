int flex1note;
double flex2note;
int flex3note;
int flex4note;
int flex1;
int flex2;
int flex3;
int flex4;
int flexbaseline;

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  a = 400;
  b = 330;
  c = 260;
  d = 190;
  x = 0;
  y = 0;
  flexbaseline = (analogRead(0) + analogRead(1) + analogRead(2) + analogRead(3))/4;
  //analogReference(INTERNAL2V56);
}

void loop() {
  while(millis() < 1000){
    flex1 = analogRead(0);
    flex2 = analogRead(1);
    flex3 = analogRead(2);
    flex4 = analogRead(3);
    flexbaseline = (flexbaseline + (flex1 + flex2 + flex3 + flex4)/4)/2
    }

  flex1 = 0;
  flex2 = 0;
  flex3 = 0;
  flex4 = 0;

  for(int i = 0; i < 10; i++){
    flex1 += analogRead(0);
    flex2 += analogRead(1);
    flex3 += analogRead(2);
    flex4 += analogRead(3);
  }
  flex1 = flex1/10;
  flex2 = flex2/10;
  flex3 = flex3/10;
  flex4 = flex4/10;

  
  while(flex1 < flexbaseline || flex2 < flexbaseline || flex3 < flexbaseline || flex4 < flexbaseline){
    if(flex1 < baseline){
      digitalWrite(9, HIGH);
      delayMicroseconds(flex1note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex1note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex1note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex1note);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*flex1note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex1note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex1note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex1note);
      digitalWrite(9, HIGH);
      delayMicroseconds(flex1note);
      digitalWrite(9, LOW);
      delayMicroseconds(26*flex1note);
    }
    if(flex2 < baseline){
      digitalWrite(9, HIGH);
      delayMicroseconds(flex2note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex2note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex2note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex2note);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*flex2note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex2note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex2note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex2note);
      digitalWrite(9, HIGH);
      delayMicroseconds(flex2note);
      digitalWrite(9, LOW);
      delayMicroseconds(26*flex2note);
    }
    if(flex3 < baseline){
      digitalWrite(9, HIGH);
      delayMicroseconds(flex3note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex3note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex3note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex3note);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*flex3note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex3note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex3note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex3note);
      digitalWrite(9, HIGH);
      delayMicroseconds(flex3note);
      digitalWrite(9, LOW);
      delayMicroseconds(26*flex3note);
    }
    if(flex4 < baseline){
      digitalWrite(9, HIGH);
      delayMicroseconds(flex4note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex4note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex4note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex4note);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*flex4note);
      digitalWrite(9, LOW);
      delayMicroseconds(3*flex4note);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*flex4note);
      digitalWrite(9, LOW);
      delayMicroseconds(6*flex4note);
      digitalWrite(9, HIGH);
      delayMicroseconds(flex4note);
      digitalWrite(9, LOW);
      delayMicroseconds(26*flex4note);
    }
  }

  /*if((millis()/50) > x){
    if(y%2 == 0){
      a = a/2;
    }else{
      a = a*2;
    }
    y = y + 1;
    x = x + 1;
  }*/
}
