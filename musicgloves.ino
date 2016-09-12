int notes [4];
int note;
int flex1;
int flex2;
int flex3;
int flex4;
int flex5;
int flex6;
int octave;
int effect;
int s;
int x;
int y;
int flexbaseline;
void sawToothNote(int note);
void sawToothDoubleNote(int note1, int note2);
void sawToothTripleNote(int note1, int note2, int note3);
void sawToothQuadNote(int note1, int note2, int note3, int note4);
void squareWaveNote(int note);
void squareWaveDoubleNote(int note1, int note2);
void squareWaveTripleNote(int note1, int note2, int note3);
void squareWaveQuadNote(int note1, int note2, int note3, int note4);
#define NOTE_A1 9088;
#define NOTE_A2 4544;
#define NOTE_A3 2272;
#define NOTE_A4 1126;
#define NOTE_A5 550;

#define NOTE_B1 8112;
#define NOTE_B2 4056;
#define NOTE_B3 2026;
#define NOTE_B4 1005;
#define NOTE_B5 490;

#define NOTE_C1 7660;
#define NOTE_C2 3830;
#define NOTE_C3 1900;
#define NOTE_C4 940;
#define NOTE_C5 475;

#define NOTE_D1 6800;
#define NOTE_D2 3400;
#define NOTE_D3 1680;
#define NOTE_D4 828;
#define NOTE_D5 400;

#define NOTE_E1 5875;
#define NOTE_E2 2918;
#define NOTE_E3 1450;
#define NOTE_E4 735;
#define NOTE_E5 352;

#define NOTE_F1 5590;
#define NOTE_F2 2785;
#define NOTE_F3 1393;
#define NOTE_F4 697;
#define NOTE_F5 342;

#define NOTE_G1 5005;
#define NOTE_G2 2500;
#define NOTE_G3 1250;
#define NOTE_G4 615;
#define NOTE_G5 292;

void setup() {
  Serial.begin(9600);
  s = 8;
  pinMode(s, OUTPUT);
  octave = 0;
  effect = 0;
  note = 0;
  notes[0] = NOTE_A1;
  notes[1] = NOTE_B1;
  notes[2] = NOTE_C1;
  notes[3] = NOTE_D1;
  x = 50;
  //y = 0;
  //get an initial single read for flexbaseline so that the initial loop read to get a flexbaseline works
  //properly(see how the next loop is designed - it needs flexbaseline to already hold a valid value)
  flexbaseline = (analogRead(0) + analogRead(1) + analogRead(2) + analogRead(3) + analogRead(4) + analogRead(5))/4;
}

void loop() {
  //for the first 1000ms of runtime this loop adds flexbaseline to itself and divides by two over and over again, getting a very accurate reading of the flex sensor when not bent
  while(millis() < 1000){
    flex1 = analogRead(0);
    flex2 = analogRead(1);
    flex3 = analogRead(2);
    flex4 = analogRead(3);
    flex5 = analogRead(4);
    //flex6 = analogRead(5);
    flexbaseline = (flexbaseline + (flex1 + flex2 + flex3 + flex4 + flex5/* + flex6*/)/5)/2;
    Serial.println("initializing flex baseline");
  }

  Serial.println("Main Loop");

  //reset all flex sensor values to zero so they can be reread
  flex1 = 0;
  flex2 = 0;
  flex3 = 0;
  flex4 = 0;
  flex5 = 0;
  //flex6 = 0;


  //average each flex sensor 10 times to get a more accurate reading
  for(int i = 0; i < 10; i++){
    flex1 += analogRead(0);
    flex2 += analogRead(1);
    flex3 += analogRead(2);
    flex4 += analogRead(3);
    flex5 += analogRead(4);
    //flex6 += analogRead(5);
  }
  flex1 = flex1/10;
  flex2 = flex2/10;
  flex3 = flex3/10;
  flex4 = flex4/10;
  flex5 = flex5/10;
  //flex6 = flex6/10;


  //if flex sensor five is activated change all notes to next octave, 1second delay to make sure it only reads once
  if(flex5 > (flexbaseline + x)){
    octave++;
    //if next spot is not a valid ocatave then return to octave 0
    if(octave > 4){
      octave = 0;
    }
    delay(1000);
  }


  //if flex sensor six is activated change the effect on the notes to the next one, 1second delay to make sure it only reads once
  /*if(flex6 > (flexbaseline + x)){
    effect++;
    //if next effect is not a valid effect then return to effect 0
    if(effect > 1){
      effect = 0;
    }
    delay(1000);
  }*/
  //depending on which octave is currently active, set notes accordingly in the notes array
  if(octave == 0){
    notes[0] = NOTE_A1;
    notes[1] = NOTE_B1;
    notes[2] = NOTE_C1;
    notes[3] = NOTE_D1;
  }else{
    if(octave == 1){
      notes[0] = NOTE_A2;
      notes[1] = NOTE_B2;
      notes[2] = NOTE_C2;
      notes[3] = NOTE_D2;
    }else{
      if(octave == 2){
        notes[0] = NOTE_A3;
        notes[1] = NOTE_B3;
        notes[2] = NOTE_C3;
        notes[3] = NOTE_D3;
      }else{
        if(octave == 3){
          notes[0] = NOTE_A4;
          notes[1] = NOTE_B4;
          notes[2] = NOTE_C4;
          notes[3] = NOTE_D4;
        }else{
          if(octave == 4){
            notes[0] = NOTE_A5;
            notes[1] = NOTE_B5;
            notes[2] = NOTE_C5;
            notes[3] = NOTE_D5;
          }
        }
      }
    }
  }


  //this is the tone making loop, there is one case for each combination of tones so that you may overly all notes on each other at the same time
  while(flex1 > (flexbaseline + x) || flex2 > (flexbaseline + x) || (flex3 > (flexbaseline + x)) || flex4 > (flexbaseline + x)){
    Serial.println("In Tone Loop");
    if(flex1 > (flexbaseline + x) && flex2 < (flexbaseline + x) && flex3 < (flexbaseline + x) && flex4 < (flexbaseline + x)){
      //depending on which effect is currently active, either make a sawtooth or a squarewave note
      if(effect == 0){
        sawToothNote(0);
      }else{
          squareWaveNote(0);
      }
    }
    if(flex2 > (flexbaseline + x) && flex1 < (flexbaseline + x) && flex3 < (flexbaseline + x) && flex4 < (flexbaseline + x)){
      if(effect == 0){
        sawToothNote(1);
      }else{
          squareWaveNote(1);
      }
    }
    if(flex3 > (flexbaseline + x) && flex1 < (flexbaseline + x) && flex2 < (flexbaseline + x) && flex4 < (flexbaseline + x)){
      if(effect == 0){
        sawToothNote(2);
      }else{
          squareWaveNote(2);
      }
    }
    if(flex4 > (flexbaseline + x) && flex1 < (flexbaseline + x) && flex2 < (flexbaseline + x) && flex3 < (flexbaseline + x)){
      if(effect == 0){
        sawToothNote(3);
      }else{
          squareWaveNote(3);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 > (flexbaseline + x) && flex3 < (flexbaseline + x) && flex4 < (flexbaseline + x)){
      if(effect == 0){
        sawToothDoubleNote(0,1);
      }else{
          squareWaveDoubleNote(0,1);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 < (flexbaseline + x) && flex3 > (flexbaseline + x) && flex4 < (flexbaseline + x)){
      if(effect == 0){
        sawToothDoubleNote(0,2);
      }else{
          squareWaveDoubleNote(0,2);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 < (flexbaseline + x) && flex3 < (flexbaseline + x) && flex4 > (flexbaseline + x)){
      if(effect == 0){
        sawToothDoubleNote(0,3);
      }else{
          squareWaveDoubleNote(0,3);
      }
    }
    if(flex1 < (flexbaseline + x) && flex2 > (flexbaseline + x) && flex3 > (flexbaseline + x) && flex4 < (flexbaseline + x)){
      if(effect == 0){
        sawToothDoubleNote(1,2);
      }else{
          squareWaveDoubleNote(1,2);
      }
    }
    if(flex1 < (flexbaseline + x) && flex2 > (flexbaseline + x) && flex3 < (flexbaseline + x) && flex4 > (flexbaseline + x)){
      if(effect == 0){
        sawToothDoubleNote(1,3);
      }else{
          squareWaveDoubleNote(1,3);
      }
    }
    if(flex1 < (flexbaseline + x) && flex2 < (flexbaseline + x) && flex3 > (flexbaseline + x) && flex4 > (flexbaseline + x)){
      if(effect == 0){
        sawToothDoubleNote(2,3);
      }else{
          squareWaveDoubleNote(2,3);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 > (flexbaseline + x) && flex3 > (flexbaseline + x) && flex4 < (flexbaseline + x)){
      if(effect == 0){
        sawToothTripleNote(0,1,2);
      }else{
          squareWaveTripleNote(0,1,2);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 > (flexbaseline + x) && flex3 < (flexbaseline + x) && flex4 > (flexbaseline + x)){
      if(effect == 0){
        sawToothTripleNote(0,1,3);
      }else{
          squareWaveTripleNote(0,1,3);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 < (flexbaseline + x) && flex3 > (flexbaseline + x) && flex4 > (flexbaseline + x)){
      if(effect == 0){
        sawToothTripleNote(0,2,3);
      }else{
          squareWaveTripleNote(0,2,3);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 > (flexbaseline + x) && flex3 > (flexbaseline + x) && flex4 < (flexbaseline + x)){
      if(effect == 0){
        sawToothTripleNote(1,2,3);
      }else{
          squareWaveTripleNote(1,2,3);
      }
    }
    if(flex1 > (flexbaseline + x) && flex2 > (flexbaseline + x) && flex3 > (flexbaseline + x) && flex4 > (flexbaseline + x)){
      if(effect == 0){
        sawToothQuadNote(0,1,2,4);
      }else{
          squareWaveQuadNote(0,1,2,4);
      }
    }
  //it is neccesary to read the flex sensor values while inside the tone making loop or else this loop will be infinite
  flex1 = 0;
  flex2 = 0;
  flex3 = 0;
  flex4 = 0;

  //we only avwerage five times inside of the loop to avoid screwing up the frequencies
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


//function to create one period of a squarewave tone at frequency 'note'
void squareWaveNote(int note){
  Serial.println("Making SquareWave Tone");
  digitalWrite(s, HIGH);
  delayMicroseconds(notes[note]);
  digitalWrite(s, LOW);
  delayMicroseconds(notes[note]);
  return;
}

//function to overlay two seperate frequency squarewave tones on top of each other simultaneously
void squareWaveDoubleNote(int note1, int note2){
  squareWaveNote(note1);
  squareWaveNote(note2);
  return;
}

//function to overlay three seperate frequency squarewave tones on top of each other simultaneously
void squareWaveTripleNote(int note1, int note2, int note3){
  squareWaveNote((2*note1)/3);
  squareWaveNote((2*note2)/3);
  squareWaveNote((2*note3)/3);
  return;
}

//function to overlay four seperate frequency squarewave tones on top of each other simultaneously
void squareWaveQuadNote(int note1, int note2, int note3, int note4){
  squareWaveNote(note1/2);
  squareWaveNote(note2/2);
  squareWaveNote(note3/2);
  squareWaveNote(note4/2);
  return;
}

//function that simulates a sawtooth wave using multiple squarewaves to create one period of a sawtooth tone at frequency 'note'
void sawToothNote(int note){
      Serial.println("Making SawTooth Tone");
      digitalWrite(s, HIGH);
      delayMicroseconds(((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(6*((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(2*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(5*((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(3*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(4*((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(4*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(2*((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(6*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(4*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(2*((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(3*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(4*((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(2*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(5*((notes[note])/61));
      digitalWrite(s, HIGH);
      delayMicroseconds(((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(6*((notes[note])/61));
      digitalWrite(s, LOW);
      delayMicroseconds(notes[note]);
      return;
}

//function to overlay two seperate frequency simulated sawtooth tones on top of each other simultaneously
void sawToothDoubleNote(int note1, int note2){
      sawToothNote(note1);
      sawToothNote(note2);
      return;
}

//function to overlay three seperate frequency simulated sawtooth tones on top of each other simultaneously
void sawToothTripleNote(int note1, int note2, int note3){
      sawToothNote((2*note1)/3);
      sawToothNote((2*note2)/3);
      sawToothNote((2*note3)/3);
      return;
}

//function to overlay four seperate frequency simulated sawtooth tones on top of each other simultaneously
void sawToothQuadNote(int note1, int note2, int note3, int note4){
      sawToothNote((note1)/2);
      sawToothNote((note2)/2);
      sawToothNote((note3)/2);
      sawToothNote((note4)/2);
      return;
}


