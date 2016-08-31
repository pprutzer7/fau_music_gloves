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
  notes[0] = 450;
  notes[1] = 350;
  notes[2] = 250;
  notes[3] = 150;
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
    if(flex1 < flexbaseline && flex2 > flexbaseline && flex3 > flexbaseline && flex4 > flexbaseline){
      sawToothNote(0);
    }
    if(flex2 < flexbaseline && flex1 > flexbaseline && flex3 > flexbaseline && flex4 > flexbaseline){
      sawToothNote(1);
    }
    if(flex3 < flexbaseline && flex1 > flexbaseline && flex2 > flexbaseline && flex4 > flexbaseline){
      sawToothNote(2);
    }
    if(flex4 < flexbaseline && flex1 > flexbaseline && flex2 > flexbaseline && flex3 > flexbaseline){
      sawToothNote(3);
    }
    if(flex1 < flexbaseline && flex2 < flexbaseline && flex3 > flexbaseline && flex4 > flexbaseline){
      sawToothDoubleNote(0,1);
    }
    if(flex1 < flexbaseline && flex2 > flexbaseline && flex3 < flexbaseline && flex4 > flexbaseline){
      sawToothDoubleNote(0,2);
    }
    if(flex1 < flexbaseline && flex2 > flexbaseline && flex3 > flexbaseline && flex4 < flexbaseline){
      sawToothDoubleNote(0,3);
    }
    if(flex1 > flexbaseline && flex2 < flexbaseline && flex3 < flexbaseline && flex4 > flexbaseline){
      sawToothDoubleNote(1,2);
    }
    if(flex1 > flexbaseline && flex2 < flexbaseline && flex3 > flexbaseline && flex4 < flexbaseline){
      sawToothDoubleNote(1,3);
    }
    if(flex1 > flexbaseline && flex2 > flexbaseline && flex3 < flexbaseline && flex4 < flexbaseline){
      sawToothDoubleNote(2,3);
    }
    if(flex1 < flexbaseline && flex2 < flexbaseline && flex3 < flexbaseline && flex4 > flexbaseline){
      sawToothTripleNote(0,1,2);
    }
    if(flex1 < flexbaseline && flex2 < flexbaseline && flex3 > flexbaseline && flex4 < flexbaseline){
      sawToothTripleNote(0,1,3);
    }
    if(flex1 < flexbaseline && flex2 > flexbaseline && flex3 < flexbaseline && flex4 < flexbaseline){
      sawToothTripleNote(0,2,3);
    }
    if(flex1 > flexbaseline && flex2 < flexbaseline && flex3 < flexbaseline && flex4 < flexbaseline){
      sawToothTripleNote(0,1,2);
    }
    if(flex1 < flexbaseline && flex2 < flexbaseline && flex3 < flexbaseline && flex4 < flexbaseline){
      sawToothQuadNote(0,1,2,3);
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

void sawToothNote(int note){
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note]);
      digitalWrite(9, LOW);
      delayMicroseconds(26*notes[note]);
      return;
}

void sawToothDoubleNote(int note1, int note2){
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note1]);
      digitalWrite(9, LOW);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(13*(notes[note1] + notes[note2]));
      return;
}

void sawToothTripleNote(int note1, int note2, int note3){
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note1]);
      digitalWrite(9, LOW);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note2]);
      digitalWrite(9, LOW);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(8*(notes[note1] + notes[note2] + notes[note3]));
      return;
}

void sawToothQuadNote(int note1, int note2, int note3, int note4){
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note1]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note1]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note1]);
      digitalWrite(9, LOW);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note2]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note2]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note2]);
      digitalWrite(9, LOW);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note3]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note3]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note3]);
      digitalWrite(9, LOW);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note4]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note4]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note4]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note4]);
      digitalWrite(9, HIGH);
      delayMicroseconds(4*notes[note4]);
      digitalWrite(9, LOW);
      delayMicroseconds(3*notes[note4]);
      digitalWrite(9, HIGH);
      delayMicroseconds(2*notes[note4]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*notes[note4]);
      digitalWrite(9, HIGH);
      delayMicroseconds(notes[note4]);
      digitalWrite(9, LOW);
      delayMicroseconds(6*(notes[note1] + notes[note2] + notes[note3] + notes[note4]));
      return;
}


