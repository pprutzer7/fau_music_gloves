int notes [4];
int note;
int flex1;
int flex2;
int flex3;
int flex4;
int x;
int y;
int flexbaseline;
void sawToothNote(int note);
void sawToothDoubleNote(int note1, int note2);
void sawToothTripleNote(int note1, int note2, int note3);
void sawToothQuadNote(int note1, int note2, int note3, int note4);

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  note = 0;
  notes[0] = 60;
  notes[1] = 50;
  notes[2] = 40;
  notes[3] = 30;
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
    flexbaseline = (flexbaseline + (flex1 + flex2 + flex3 + flex4)/4)/2;
    }
    //Serial.println("flexbaseline");
    //Serial.println(flexbaseline);
    /*Serial.println("flex1");
    Serial.println(flex1);
    Serial.println("flex2");
    Serial.println(flex2);*/

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

  
  while(flex1 > (flexbaseline + 50) || flex2 > (flexbaseline + 50) || (flex3 > (flexbaseline + 50)) || flex4 > (flexbaseline + 50)){
    if(flex1 > (flexbaseline + 50) && flex2 < (flexbaseline + 50) && flex3 < (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothNote(0);
    }
    if(flex2 > (flexbaseline + 50) && flex1 < (flexbaseline + 50) && flex3 < (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothNote(1);
    }
    if(flex3 > (flexbaseline + 50) && flex1 < (flexbaseline + 50) && flex2 < (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothNote(2);
    }
    if(flex4 > (flexbaseline + 50) && flex1 < (flexbaseline + 50) && flex2 < (flexbaseline + 50) && flex3 < (flexbaseline + 50)){
      sawToothNote(3);
    }
    if(flex1 > (flexbaseline + 50) && flex2 > (flexbaseline + 50) && flex3 < (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothDoubleNote(0,1);
    }
    if(flex1 > (flexbaseline + 50) && flex2 < (flexbaseline + 50) && flex3 > (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothDoubleNote(0,2);
    }
    if(flex1 > (flexbaseline + 50) && flex2 < (flexbaseline + 50) && flex3 < (flexbaseline + 50) && flex4 > (flexbaseline + 50)){
      sawToothDoubleNote(0,3);
    }
    if(flex1 < (flexbaseline + 50) && flex2 > (flexbaseline + 50) && flex3 > (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothDoubleNote(1,2);
    }
    if(flex1 < (flexbaseline + 50) && flex2 > (flexbaseline + 50) && flex3 < (flexbaseline + 50) && flex4 > (flexbaseline + 50)){
      sawToothDoubleNote(1,3);
    }
    if(flex1 < (flexbaseline + 50) && flex2 < (flexbaseline + 50) && flex3 > (flexbaseline + 50) && flex4 > (flexbaseline + 50)){
      sawToothDoubleNote(2,3);
    }
    if(flex1 > (flexbaseline + 50) && flex2 > (flexbaseline + 50) && flex3 > (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothTripleNote(0,1,2);
    }
    if(flex1 > (flexbaseline + 50) && flex2 > (flexbaseline + 50) && flex3 < (flexbaseline + 50) && flex4 > (flexbaseline + 50)){
      sawToothTripleNote(0,1,3);
    }
    if(flex1 > (flexbaseline + 50) && flex2 < (flexbaseline + 50) && flex3 > (flexbaseline + 50) && flex4 > (flexbaseline + 50)){
      sawToothTripleNote(0,2,3);
    }
    if(flex1 > (flexbaseline + 50) && flex2 > (flexbaseline + 50) && flex3 > (flexbaseline + 50) && flex4 < (flexbaseline + 50)){
      sawToothTripleNote(0,1,2);
    }
    if(flex1 > (flexbaseline + 50) && flex2 > (flexbaseline + 50) && flex3 > (flexbaseline + 50) && flex4 > (flexbaseline + 50)){
      sawToothQuadNote(0,1,2,3);
    }
  flex1 = 0;
  flex2 = 0;
  flex3 = 0;
  flex4 = 0;

  for(int i = 0; i < 5; i++){
    flex1 += analogRead(0);
    flex2 += analogRead(1);
    flex3 += analogRead(2);
    flex4 += analogRead(3);
  }
  flex1 = flex1/5;
  flex2 = flex2/5;
  flex3 = flex3/5;
  flex4 = flex4/5;
  }
}

void sawToothNote(int note){
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(5*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(3*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(4*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(2*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(6*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(2*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(3*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(4*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(5*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(62*notes[note]);
      return;
}

void sawToothDoubleNote(int note1, int note2){
      sawToothNote(note1);
      sawToothNote(note2);
      return;
}

void sawToothTripleNote(int note1, int note2, int note3){
      sawToothNote((2*note1)/3);
      sawToothNote((2*note2)/3);
      sawToothNote((2*note3)/3);
      return;
}
void sawToothQuadNote(int note1, int note2, int note3, int note4){
      sawToothNote((note1)/2);
      sawToothNote((note2)/2);
      sawToothNote((note3)/2);
      sawToothNote((note4)/2);
      return;
}


