#include <SoftwareSerial.h>
int notes [7];
int note;
byte rxPin = 10;
byte txPin = 11;
SoftwareSerial serialconnection(rxPin, txPin);
byte input [5];
byte junk [5];
int doweupdate;
int r1;
int r2;
int r3;
int r4;
int r5;
int yy;
//int et;
int previousR[5];
int wait;
int buff;
int count;
int flex1;
int flex2;
int flex3;
int flex4;
int flex5;
int flex6;
int flex7;
int flex8;
int flex9;
int flex10;
int fonote;
int focount;
int octave;
int effect;
int s;
int fcount;
int focountlast;
int x;
float p1;
float p2;
float p3;
float p4;
float p5;
float p6;
float p7;
float pk;
float px;
float py;
float pz;
float pt;
float pt2;
float pt3;
float pt4;
int rebaseline;
int y;
int rv;
int flexbaseline;
void sawToothNote(int note);
void triangleWaveNote(int note);
void squareWaveNote(int note);


#define NOTE_A1 8950;
#define NOTE_A2 4450;
#define NOTE_A3 2150;
#define NOTE_A4 1015;
#define NOTE_A5 444;

#define NOTE_B1 8000;
#define NOTE_B2 4000;
#define NOTE_B3 1900;
#define NOTE_B4 900;
#define NOTE_B5 385;

#define NOTE_C1 7450;
#define NOTE_C2 3700;
#define NOTE_C3 1750;
#define NOTE_C4 825;
#define NOTE_C5 353;

#define NOTE_D1 6700;
#define NOTE_D2 3280;
#define NOTE_D3 1577;
#define NOTE_D4 730;
#define NOTE_D5 305;


#define NOTE_E1 5925;
#define NOTE_E2 2940;
#define NOTE_E3 1392;
#define NOTE_E4 640;
#define NOTE_E5 260;


#define NOTE_F1 5650;
#define NOTE_F2 2760;
#define NOTE_F3 1320;
#define NOTE_F4 600;
#define NOTE_F5 230;


#define NOTE_G1 5005;
#define NOTE_G2 2395;
#define NOTE_G3 1170;
#define NOTE_G4 520;
#define NOTE_G5 190;

#define NOTE_Ab2 4800;
#define NOTE_Ab3 2350;
#define NOTE_Ab4 1176;
#define NOTE_Ab5 565;

#define NOTE_Bb1 8400;
#define NOTE_Bb2 4250;
#define NOTE_Bb3 2102;
#define NOTE_Bb4 1047;
#define NOTE_Bb5 507;

void setup() {
  while (!Serial) ;
  Serial.begin(38400);
  s = 8;
  pinMode(s, OUTPUT);
  randomSeed(2);
  octave = 0;
  effect = 0;
  note = 0;
  fonote = 0;
  count = 0;
  //rxPin = 10;
  //txPin = 11;
  serialconnection.begin(38400);
  serialconnection.setTimeout(5);
  notes[0] = NOTE_C1;
  notes[1] = NOTE_D1;
  notes[2] = NOTE_E1;
  notes[3] = NOTE_F1;
  notes[4] = NOTE_G1;
  notes[5] = NOTE_A1;
  notes[6] = NOTE_B1;
  x = 150;
  p1 = 0;
  p2 = 0;
  p3 = 0;
  p4 = 0;
  p5 = 0;
  p6 = 0;
  p7 = 0;
  fcount = 1;
  focount = 0;
  focountlast = -1;
  y = 0;
  //get an initial single read for flexbaseline so that the initial loop read to get a flexbaseline works
  //properly(see how the next loop is designed - it needs flexbaseline to already hold a valid value)
  flexbaseline = (analogRead(0) + analogRead(1) + analogRead(2) + analogRead(3) + analogRead(5)) / 5;

  previousR[0] = flexbaseline;
  previousR[1] = flexbaseline;
  previousR[2] = flexbaseline;
  previousR[3] = flexbaseline;
  previousR[4] = flexbaseline;
  r1 = 0;
  r2 = 0;
  r3 = 0;
  r4 = 0;
  r5 = 0;
}

void loop() {
  //for the first 1000ms of runtime this loop adds flexbaseline to itself and divides by two over and over again, getting a very accurate reading of the flex sensor when not bent
  y = millis();
  rebaseline = y / 1000;
  if ((rebaseline % 10 == 0)){
    if(flex1 < (flexbaseline + x) && flex2 < (flexbaseline + x) && flex3 < (flexbaseline + x) && flex4 < (flexbaseline + x) && flex7 < (flexbaseline + x) && flex8 < (flexbaseline + x) && flex9 < (flexbaseline + x)){
    if((flex6 != 0) && (flex7 != 0) && (flex8 != 0) && (flex9 != 0) && (flex10 != 0)) {
  
    flexbaseline = (analogRead(0) + analogRead(1) + analogRead(2) + analogRead(3) + analogRead(5)+ flex6 + flex7 + flex8 + flex9 + flex10) / 10;
    while (millis() - y < 100) {
      flex1 = analogRead(0);
      flex2 = analogRead(1);
      flex3 = analogRead(2);
      flex4 = analogRead(3);
      flex5 = analogRead(4);
      flexbaseline = (flexbaseline + (flex1 + flex2 + flex3 + flex4 + flex5 + flex6 + flex7 + flex8 + flex9 + flex10) / 10) / 2;
      Serial.println("initializing flex baseline");
    }
    pk = 1024 - (flexbaseline + 50);
  }
  }
  }

  Serial.println("Main Loop");

  delay(25);
  if (serialconnection.available() > 4) {
    Serial.println("reading right glove outside tone loop");
    doweupdate = serialconnection.readBytes(input, 5);
    if (doweupdate == 5) {
      Serial.println("resetting values for right glove outside tone loop");
      r1 = input[0] * 4;
      r2 = input[1] * 4;
      r3 = input[2] * 4;
      r4 = input[3] * 4;
      r5 = input[4] * 4;
    } else {
      if (doweupdate > 0) {
        Serial.println("throwing out junk for right glove outside tone loop");
        junk[0] = input[0];
        junk[1] = input[1];
        junk[2] = input[2];
        junk[3] = input[3];
        junk[4] = input[4];
      }
    }
  }


  //reset all flex sensor values to zero so they can be reread
  flex1 = 0;
  flex2 = 0;
  flex3 = 0;
  flex4 = 0;
  flex5 = 0;
  flex6 = r4;
  flex7 = r2;
  flex8 = r1;
  flex9 = r5;
  flex10 = r3;


  //average each flex sensor 10 times to get a more accurate reading
  for (int i = 0; i < 10; i++) {
    flex1 += analogRead(0);
    flex2 += analogRead(1);
    flex3 += analogRead(2);
    flex4 += analogRead(3);
    flex5 += analogRead(5);
    //flex6 += analogRead(5);
  }
  flex1 = flex1 / 10;
  flex2 = flex2 / 10;
  flex3 = flex3 / 10;
  flex4 = flex4 / 10;
  flex5 = flex5 / 10;
  //flex6 = flex6/10;


  //if flex sensor five is activated change all notes to next octave, 1second delay to make sure it only reads once
  if (flex5 > (flexbaseline + (x + 50))) {
    y = millis();
      while((millis() - y) < 60){
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(6);
        }
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(0);
        }
      }
    for (int i = 0; i < 5; i++) {
      flex5 += analogRead(5);
    }
    flex5 = flex5 / 5;
    if (flex5 > (flexbaseline + (x + 50))) {
      octave++;
      //if next spot is not a valid ocatave then return to octave 0
      if (octave > 4) {
        octave = 0;
      }
      
      delay(600);
    }
    focount = 2;
    focountlast = 1;
    fcount = 2;
  }


  //if flex sensor six is activated change the effect on the notes to the next one, 1second delay to make sure it only reads once
  if (flex6 > (flexbaseline + x)) {
    Serial.println("effects finger triggered");
    if (flex6 > (flexbaseline + x)) {
      
      effect++;
      //if next effect is not a valid effect then return to effect 0
      if (effect > 11) {
        effect = 0;
      }
      y = millis();
      while((millis() - y) < 60){
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(6);
        }
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(0);
        }
      }
      //et = effect;
      y = millis();
      while ((millis() - y) < 600) {
        if (serialconnection.available() > 4) {
          doweupdate = serialconnection.readBytes(input, 5);
          if (doweupdate == 5) {
            r1 = input[0] * 4;
            r2 = input[1] * 4;
            r3 = input[2] * 4;
            r4 = input[3] * 4;
            r5 = input[4] * 4;
          } else {
            if (doweupdate > 0) {
              junk[0] = input[0];
              junk[1] = input[1];
              junk[2] = input[2];
              junk[3] = input[3];
              junk[4] = input[4];
            }
          }
        }
      }
      flex6 = r4;
      /*effect = 6;
      y = millis();
      while((millis() - y) < 150){
      sawToothNote(6);
      //sawToothNote();*/
      //}
      focount = 2;
      focountlast = 1;
      fcount = 2;
      
      //effect = et;
    }
    
  }
  //depending on which octave is currently active, set notes accordingly in the notes array
  if (octave == 0) {
    notes[0] = NOTE_A1;
    notes[1] = NOTE_D1;
    notes[2] = NOTE_E1;
    notes[3] = NOTE_F1;
    notes[4] = NOTE_G1;
    notes[5] = NOTE_A1;
    notes[6] = NOTE_B1;
  } else {
    if (octave == 1) {
      notes[0] = NOTE_C2;
      notes[1] = NOTE_D2;
      notes[2] = NOTE_E2;
      notes[3] = NOTE_F2;
      notes[4] = NOTE_G2;
      notes[5] = NOTE_A2;
      notes[6] = NOTE_B2;
    } else {
      if (octave == 2) {
        notes[0] = NOTE_C3;
        notes[1] = NOTE_D3;
        notes[2] = NOTE_E3;
        notes[3] = NOTE_F3;
        notes[4] = NOTE_G3;
        notes[5] = NOTE_A3;
        notes[6] = NOTE_B3;
      } else {
        if (octave == 3) {
          notes[0] = NOTE_C4;
          notes[1] = NOTE_D4;
          notes[2] = NOTE_E4;
          notes[3] = NOTE_F4;
          notes[4] = NOTE_G4;
          notes[5] = NOTE_A4;
          notes[6] = NOTE_B4;
        } else {
          if (octave == 4) {
            notes[0] = NOTE_C5;
            notes[1] = NOTE_D5;
            notes[2] = NOTE_E5;
            notes[3] = NOTE_F5;
            notes[4] = NOTE_G5;
            notes[5] = NOTE_A5;
            notes[6] = NOTE_B5;
          }
        }
      }
    }
  }

  focount = 2;
  focountlast = 1;
  fcount = 2;
  Serial.println("NOT IN TONE LOOP");
  Serial.println("OCTAVE");
  Serial.println(octave);
  Serial.println("EFFECT");
  Serial.println(effect);
  Serial.print(flex1);
  Serial.print(" : ");
  Serial.print(flex2);
  Serial.print(" : ");
  Serial.print(flex3);
  Serial.print(" : ");
  Serial.print(flex4);
  Serial.print(" : ");
  Serial.print(flex5);
  Serial.print(" : ");
  Serial.print(flex6);
  Serial.print(" : ");
  Serial.print(flex7);
  Serial.print(" : ");
  Serial.print(flex8);
  Serial.print(" : ");
  Serial.print(flex9);
  Serial.print(" : ");
  Serial.print(flex10);
  Serial.print(" : ");
  Serial.print(flexbaseline);
  Serial.print(" : ");

  rv = 0;
  //this is the tone making loop, there is one case for each combination of tones so that you may overly all notes on each other at the same time
  while (flex1 > (flexbaseline + (x - 50)) || flex2 > (flexbaseline + x) || flex3 > (flexbaseline + x) || flex4 > (flexbaseline + x) || flex7 > (flexbaseline + x) || flex8 > (flexbaseline + x) || flex9 > (flexbaseline + x)) {
    Serial.println("In Tone Loop");
    Serial.println("OCTAVE");
    Serial.println(octave);
    Serial.println("EFFECT");
    Serial.println(effect);
    Serial.print(flex1);
    Serial.print(" : ");
    Serial.print(flex2);
    Serial.print(" : ");
    Serial.print(flex3);
    Serial.print(" : ");
    Serial.print(flex4);
    Serial.print(" : ");
    Serial.print(flex5);
    Serial.print(" : ");
    Serial.print(flex6);
    Serial.print(" : ");
    Serial.print(flex7);
    Serial.print(" : ");
    Serial.print(flex8);
    Serial.print(" : ");
    Serial.print(flex9);
    Serial.print(" : ");
    Serial.print(flex10);
    Serial.print(" : ");
    Serial.print(flexbaseline);
    Serial.print(" : ");
    p1 = (flex1 - (flexbaseline + 50)) / pk;
    p2 = (flex2 - (flexbaseline + 50)) / pk;
    p3 = (flex3 - (flexbaseline + 50)) / pk;
    p4 = (flex4 - (flexbaseline + 50)) / pk;
    p5 = (flex7 - (flexbaseline + 50)) / pk;
    p6 = (flex8 - (flexbaseline + 50)) / pk;
    p7 = (flex9 - (flexbaseline + 50)) / pk;



    if (flex1 > (flexbaseline + (x - 50))) {
      //depending on which effect is currently active, either make a sawTooth wave a triangleWave note or default to a squarewave note to be used with any other effects
      if (effect == 0 || effect == 1 || effect == 2) {
        squareWaveNote(0, p1);
      } else {
        if (effect == 3 || effect == 4 || effect == 5) {
          triangleWaveNote(0);
        } else {
          if (effect == 6 || effect == 7 || effect == 8) {
            sawToothNote(0);
          }
          else{
            if(effect == 9 || effect == 10 || effect == 11){
              halfSine(0);
            }
          }
        }
      }
    }

    if (flex2 > (flexbaseline + x)) {
      //depending on which effect is currently active, either make a sawTooth wave a triangleWave note or default to a squarewave note to be used with any other effects
      if (effect == 0 || effect == 1 || effect == 2) {
        squareWaveNote(1, p2);
      } else {
        if (effect == 3 || effect == 4 || effect == 5) {
          triangleWaveNote(1);
        } else {
          if (effect == 6 || effect == 7 || effect == 8) {
            sawToothNote(1);
          }
          else{
            if(effect == 9 || effect == 10 || effect == 11){
              halfSine(1);
            }
          }
        }
      }
    }

    if (flex3 > (flexbaseline + x)) {
      //depending on which effect is currently active, either make a sawTooth wave a triangleWave note or default to a squarewave note to be used with any other effects
      if (effect == 0 || effect == 1 || effect == 2) {
        squareWaveNote(2, p3);
      } else {
        if (effect == 3 || effect == 4 || effect == 5) {
          triangleWaveNote(2);
        } else {
          if (effect == 6 || effect == 7 || effect == 8) {
            sawToothNote(2);
          }
          else{
            if(effect == 9 || effect == 10 || effect == 11){
              halfSine(2);
            }
          }
        }
      }
    }

    if (flex4 > (flexbaseline + x)) {
      //depending on which effect is currently active, either make a sawTooth wave a triangleWave note or default to a squarewave note to be used with any other effects
      if (effect == 0 || effect == 1 || effect == 2) {
        squareWaveNote(3, p4);
      } else {
        if (effect == 3 || effect == 4 || effect == 5) {
          triangleWaveNote(3);
        } else {
          if (effect == 6 || effect == 7 || effect == 8) {
            sawToothNote(3);
          }
          else{
            if(effect == 9 || effect == 10 || effect == 11){
              halfSine(3);
            }
          }
        }
      }
    }

    if (flex7 > (flexbaseline + x)) {
      //depending on which effect is currently active, either make a sawTooth wave a triangleWave note or default to a squarewave note to be used with any other effects
      if (effect == 0 || effect == 1 || effect == 2) {
        squareWaveNote(4, p5);
      } else {
        if (effect == 3 || effect == 4 || effect == 5) {
          triangleWaveNote(4);
        } else {
          if (effect == 6 || effect == 7 || effect == 8) {
            sawToothNote(4);
          }
          else{
            if(effect == 9 || effect == 10 || effect == 11){
              halfSine(4);
            }
          }
        }
      }
    }

    if (flex8 > (flexbaseline + x)) {
      //depending on which effect is currently active, either make a sawTooth wave a triangleWave note or default to a squarewave note to be used with any other effects
      if (effect == 0 || effect == 1 || effect == 2) {
        squareWaveNote(5, p6);
      } else {
        if (effect == 3 || effect == 4 || effect == 5) {
          triangleWaveNote(5);
        } else {
          if (effect == 6 || effect == 7 || effect == 8) {
            sawToothNote(5);
          }
          else{
            if(effect == 9 || effect == 10 || effect == 11){
              halfSine(5);
            }
          }
        }
      }
    }

    if (flex9 > (flexbaseline + x)) {
      //depending on which effect is currently active, either make a sawTooth wave a triangleWave note or default to a squarewave note to be used with any other effects
      if (effect == 0 || effect == 1 || effect == 2) {
        squareWaveNote(6, p7);
      } else {
        if (effect == 3 || effect == 4 || effect == 5) {
          triangleWaveNote(6);
        } else {
          if (effect == 6 || effect == 7 || effect == 8) {
            sawToothNote(6);
          }else{
            if(effect == 9 || effect == 10 || effect == 11){
              halfSine(6);
            }
          }
        }
      }
    }










    //it is neccesary to read the flex sensor values while inside the tone making loop or else this loop will be infinite
    flex1 = 0;
    flex2 = 0;
    flex3 = 0;
    flex4 = 0;
    flex5 = 0;

    //we only avwerage five times inside of the loop to avoid screwing up the frequencies
    for (int i = 0; i < 3; i++) {
      flex1 += analogRead(0);
      flex2 += analogRead(1);
      flex3 += analogRead(2);
      flex4 += analogRead(3);
      flex5 += analogRead(5);
    }
    flex1 = flex1 / 3;
    flex2 = flex2 / 3;
    flex3 = flex3 / 3;
    flex4 = flex4 / 3;
    flex5 = flex5 / 3;

    if (serialconnection.available() > 4) {
      Serial.println("reading right glove");
      doweupdate = serialconnection.readBytes(input, 5);
      if (doweupdate == 5) {
        Serial.println("updating values on right glove");
        r1 = input[0] * 4;
        r2 = input[1] * 4;
        r3 = input[2] * 4;
        r4 = input[3] * 4;
        r5 = input[4] * 4;
      } else {
        if (doweupdate > 0) {
          Serial.println("throwing out junk values for right glove");
          junk[0] = input[0];
          junk[1] = input[1];
          junk[2] = input[2];
          junk[3] = input[3];
          junk[4] = input[4];
        }
      }
  flex6 = r4;
  flex7 = r2;
  flex8 = r1;
  flex9 = r5;
  flex10 = r3;
    }

    if (flex6 > (flexbaseline + x)) {
    Serial.println("effects finger triggered");
    if (flex6 > (flexbaseline + x)) {
      
      effect++;
      //if next effect is not a valid effect then return to effect 0
      if (effect > 11) {
        effect = 0;
      }
      y = millis();
      while((millis() - y) < 60){
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(6);
        }
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(0);
        }
      }
      //et = effect;
      y = millis();
      while ((millis() - y) < 200) {
        if (serialconnection.available() > 4) {
          doweupdate = serialconnection.readBytes(input, 5);
          if (doweupdate == 5) {
            r1 = input[0] * 4;
            r2 = input[1] * 4;
            r3 = input[2] * 4;
            r4 = input[3] * 4;
            r5 = input[4] * 4;
          } else {
            if (doweupdate > 0) {
              junk[0] = input[0];
              junk[1] = input[1];
              junk[2] = input[2];
              junk[3] = input[3];
              junk[4] = input[4];
            }
          }
        }
      }
      flex6 = r4;
      /*effect = 6;
      y = millis();
      while((millis() - y) < 150){
      sawToothNote(6);
      //sawToothNote();*/
      //}
      focount = 2;
      focountlast = 1;
      fcount = 2;
      
      //effect = et;
    }
    
  }

  if (flex5 > (flexbaseline + (x + 50))) {
    y = millis();
      while((millis() - y) < 60){
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(6);
        }
        yy = millis();
        while((millis() - yy) < 15){
        sawToothNote(0);
        }
      }
    for (int i = 0; i < 5; i++) {
      flex5 += analogRead(5);
    }
    flex5 = flex5 / 5;
    if (flex5 > (flexbaseline + (x + 50))) {
      octave++;
      //if next spot is not a valid ocatave then return to octave 0
      if (octave > 4) {
        octave = 0;
      }
      
      delay(100);
    }
    focount = 2;
    focountlast = 1;
    fcount = 2;

    if (octave == 0) {
    notes[0] = NOTE_A1;
    notes[1] = NOTE_D1;
    notes[2] = NOTE_E1;
    notes[3] = NOTE_F1;
    notes[4] = NOTE_G1;
    notes[5] = NOTE_A1;
    notes[6] = NOTE_B1;
  } else {
    if (octave == 1) {
      notes[0] = NOTE_C2;
      notes[1] = NOTE_D2;
      notes[2] = NOTE_E2;
      notes[3] = NOTE_F2;
      notes[4] = NOTE_G2;
      notes[5] = NOTE_A2;
      notes[6] = NOTE_B2;
    } else {
      if (octave == 2) {
        notes[0] = NOTE_C3;
        notes[1] = NOTE_D3;
        notes[2] = NOTE_E3;
        notes[3] = NOTE_F3;
        notes[4] = NOTE_G3;
        notes[5] = NOTE_A3;
        notes[6] = NOTE_B3;
      } else {
        if (octave == 3) {
          notes[0] = NOTE_C4;
          notes[1] = NOTE_D4;
          notes[2] = NOTE_E4;
          notes[3] = NOTE_F4;
          notes[4] = NOTE_G4;
          notes[5] = NOTE_A4;
          notes[6] = NOTE_B4;
        } else {
          if (octave == 4) {
            notes[0] = NOTE_C5;
            notes[1] = NOTE_D5;
            notes[2] = NOTE_E5;
            notes[3] = NOTE_F5;
            notes[4] = NOTE_G5;
            notes[5] = NOTE_A5;
            notes[6] = NOTE_B5;
          }
        }
      }
    }
  }

    
  }
    
  }


}


//function to create one period of a squarewave tone at frequency 'note'
void squareWaveNote(int note, float p) {
  if (effect == 0) {
    Serial.println("Making Regular SquareWave Tone");
    Serial.println(p);
    digitalWrite(s, HIGH);
    delayMicroseconds(notes[note] + p * (notes[note]));
    digitalWrite(s, LOW);
    delayMicroseconds(notes[note] - p * (notes[note]));
  } else {
    if (effect == 1) {
      //fcount++;
      rv += (5 - octave)*30;
      if(rv > (3*(notes[note])/4)){
        rv = 0;
      }
      //rv = rv + (rv/(octave + 2));
      Serial.println("Making Flange SquareWave Tone");
      digitalWrite(s, HIGH);
      delayMicroseconds((notes[note]));
      delayMicroseconds(rv);
      digitalWrite(s, LOW);
      delayMicroseconds(((notes[note])) - rv);
      
      /*if (fcount > 15) {
        fcount = 2;
      }*/
    } else {
      if (effect == 2) {
        Serial.println("Making Frequency Oscillating SquareWave Tone");
        fonote = notes[note] + (focount * (notes[note])) / 20;
        if (focount > (3 + octave)) {
          focount = focountlast - 1;
        }
        if (focount < (-3 - octave)) {
          focount = focountlast + 1;
        }
        Serial.println(p);
        digitalWrite(s, HIGH);
        delayMicroseconds(fonote + (p * fonote));
        digitalWrite(s, LOW);
        delayMicroseconds(fonote - (p * fonote));
        
        if (focountlast < focount) {
          focountlast = focount;
          focount++;
        } else {
          focountlast = focount;
          focount--;
        }
      }
    }
  }
  return;
}


//function that simulates a triangleWave wave using multiple squarewaves to create one period of a triangleWave tone at frequency 'note'
void triangleWaveNote(int note) {
  if (effect == 3) {
    Serial.println("Making Regular triangleWave Tone");
    digitalWrite(s, HIGH);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(6 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(5 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(6 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(5 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(6 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(notes[note]);
  } else {
    if(effect == 4){
      Serial.println("Making Flange triangleWave Tone");
      //fcount++;
      rv += (5 - octave)*50;
      if(rv > (3*(notes[note])/4)){
        rv = 0;
      }
    digitalWrite(s, HIGH);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(6 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(5 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds((6 * (notes[note])) / 30);
    delayMicroseconds(notes[note] - rv);
    digitalWrite(s, LOW);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(5 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(6 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(notes[note]);
    delayMicroseconds(rv);
    /*if (fcount > 10) {
        fcount = 2;
      }*/
    }else{
    if (effect == 5) {
      Serial.println("Making Frequency Oscillating triangleWave Tone");
      fonote = notes[note] + (focount * (notes[note])) / 20;
      if (focount > (3 + octave)) {
        focount = focountlast - 1;
      }
      if (focount < (-3 - octave)) {
        focount = focountlast + 1;
      }
      digitalWrite(s, HIGH);
      delayMicroseconds(((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(6 * ((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(2 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(5 * ((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(3 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(4 * ((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(4 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(2 * ((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(6 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(4 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(2 * ((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(3 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(4 * ((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(2 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(5 * ((fonote) / 30));
      digitalWrite(s, HIGH);
      delayMicroseconds(((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(6 * ((fonote) / 30));
      digitalWrite(s, LOW);
      delayMicroseconds(fonote);
      if (focountlast < focount) {
        focountlast = focount;
        focount++;
      } else {
        focountlast = focount;
        focount--;
      }
    }
    }
  }
    
    return;
  }


  //function that simulates a sawTooth wave using multiple squarewaves to create one period of a sawTooth tone at frequency 'note'
  void sawToothNote(int note) {
    if((effect == 6) || (effect == 0) || (effect == 3)  || (effect == 9)){
    Serial.println("Making Regular sawTooth Tone");
    digitalWrite(s, HIGH);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(5 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(5 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(notes[note]);
    }else{
      if((effect == 7) || (effect == 1) || (effect == 4) || (effect == 10)){
        Serial.println("Making Flange sawTooth Tone");
        //fcount++;
      rv += (5 - octave)*50;
      if(rv > (3*(notes[note])/4)){
        rv = 0;
      }
    digitalWrite(s, HIGH);
    delayMicroseconds(((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(5 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(3 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(4 * ((notes[note]) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(5 * ((notes[note]) / 30));
    delayMicroseconds(rv);
    digitalWrite(s, LOW);
    delayMicroseconds(notes[note] - rv);
    /*if (fcount > 10) {
        fcount = 2;
      }*/
      }else{
        if((effect == 8) || (effect == 2) || (effect == 5) || (effect == 11)){
          Serial.println("Making Frequency Oscillation sawTooth Tone");
          fonote = notes[note] + (focount * (notes[note])) / 20;
      if (focount > (3 + octave)) {
        focount = focountlast - 1;
      }
      if (focount < (-3 - octave)) {
        focount = focountlast + 1;
      }
      digitalWrite(s, HIGH);
    delayMicroseconds(((fonote) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(5 * ((fonote) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((fonote) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((fonote) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((fonote) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(3 * ((fonote) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(4 * ((fonote) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((fonote) / 30));
    digitalWrite(s, HIGH);
    delayMicroseconds(5 * ((fonote) / 30));
    digitalWrite(s, LOW);
    delayMicroseconds(fonote);
    if (focountlast < focount) {
      focountlast = focount;
        focount++;
      } else {
        focountlast = focount;
        focount--;
      }
        }
      }
    }
    return;
  }

  void halfSine(int note) {
    if((effect == 9)){
    Serial.println("Making Regular halfSine Tone");
    digitalWrite(s, HIGH);
    delayMicroseconds(2 *((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(3 *((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(4*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(6*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(10*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(10*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(6*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(4*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4*((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(3 *((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(2 *((notes[note]) / 80));
    delayMicroseconds(notes[note]);
    }else{
      if((effect == 10)){
        Serial.println("Making Flange halfSine Tone");
        rv += (5 - octave)*50;
      if(rv > (3*(notes[note])/4)){
        rv = 0;
      }
      digitalWrite(s, HIGH);
    delayMicroseconds(2 *((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(3 *((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(4*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(6*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(10*((notes[note]) / 80));
    delayMicroseconds(rv);
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(10*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(6*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(4*((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4*((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(3 *((notes[note]) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((notes[note]) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(2 *((notes[note]) / 80));
    delayMicroseconds(notes[note]);
    delayMicroseconds(notes[note] - rv);
      }else{
        if(effect == 11){
          Serial.println("Making Frequency Oscillating halfSine Tone");
        fonote = notes[note] + (focount * (notes[note])) / 20;
        if (focount > (3 + octave)) {
          focount = focountlast - 1;
        }
        if (focount < (-3 - octave)) {
          focount = focountlast + 1;
        }

        Serial.println("Making Regular halfSine Tone");
    digitalWrite(s, HIGH);
    delayMicroseconds(2 *((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(2 * ((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(3 *((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(4*((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(6*((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(10*((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(10*((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(6*((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4 * ((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(4*((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(4*((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(3 * ((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(3 *((fonote) / 80));
    digitalWrite(s, HIGH);
    delayMicroseconds(2 * ((fonote) / 80));
    digitalWrite(s, LOW);
    delayMicroseconds(2 *((fonote) / 80));
    delayMicroseconds(fonote);
        if (focountlast < focount) {
      focountlast = focount;
        focount++;
      } else {
        focountlast = focount;
        focount--;
      }
        }
      }
    }
  }

