
#define NOTE_A1 9088 
#define NOTE_A2 4544 
#define NOTE_A3 2272
#define NOTE_A4 1126
#define NOTE_A5 550


#define NOTE_Ab1 9550
#define NOTE_Ab2 4800
#define NOTE_Ab3 2350
#define NOTE_Ab4 1176
#define NOTE_Ab5 565

#define NOTE_B1 8112
#define NOTE_B2 4056
#define NOTE_B3 2026
#define NOTE_B4 1005
#define NOTE_B5 490

#define NOTE_Bb1 8400
#define NOTE_Bb2 4250
#define NOTE_Bb3 2102
#define NOTE_Bb4 1047
#define NOTE_Bb5 507

#define NOTE_C1 7660
#define NOTE_C2 3830
#define NOTE_C3 1900
#define NOTE_C4 940
#define NOTE_C5 475

#define NOTE_D1 6800
#define NOTE_D2 3400
#define NOTE_D3 1680
#define NOTE_D4 828
#define NOTE_D5 400

#define NOTE_Db1 7250
#define NOTE_Db2 3600
#define NOTE_Db3 1760
#define NOTE_Db4 860
#define NOTE_Db5 420

#define NOTE_E1 5875
#define NOTE_E2 2918
#define NOTE_E3 1450
#define NOTE_E4 735
#define NOTE_E5 352

#define NOTE_Eb1 6400
#define NOTE_Eb2 3200
#define NOTE_Eb3 1543
#define NOTE_Eb4 758
#define NOTE_Eb5 365

#define NOTE_F1 5590
#define NOTE_F2 2785
#define NOTE_F3 1393
#define NOTE_F4 697
#define NOTE_F5 342

#define NOTE_Gb1 5400
#define NOTE_Gb2 2660
#define NOTE_Gb3 1315
#define NOTE_Gb4 645
#define NOTE_Gb5 300

#define NOTE_G1 5005
#define NOTE_G2 2500
#define NOTE_G3 1250
#define NOTE_G4 615
#define NOTE_G5 292



//First 4 notes in scale
int Flex_1 = A0;
int Flex_2 = A1;
int Flex_3 = A2;
int Flex_4 = A3;

//Octave Switch
int Flex_5 = A4;

//Output
int audio = 8;

int Flex_1_value = 0;
int Flex_2_value = 0;
int Flex_3_value = 0;
int Flex_4_value = 0;
int Flex_5_value = 0;

void setup() 
{
  pinMode(audio, OUTPUT);
    
  Serial.begin(9600);
}

void loop() 
{

      Flex_5_value = analogRead(Flex_5);

      if(Flex_5_value >= 400)
      {
        digitalWrite(audio, HIGH);
      }
 
      Flex_4_value = analogRead(Flex_4);
 
      if(Flex_4_value >= 400)
      {
      digitalWrite(audio, HIGH);
      delayMicroseconds(NOTE_F2);
      digitalWrite(audio, LOW);
      delayMicroseconds(NOTE_F2);
      }

      Flex_3_value = analogRead(Flex_3);
 
      if(Flex_3_value >= 400)
      {
      digitalWrite(audio, HIGH);
      delayMicroseconds(NOTE_E2);
      digitalWrite(audio, LOW);
      delayMicroseconds(NOTE_E2);
      }
      Flex_2_value = analogRead(Flex_2);
 
      if(Flex_2_value >= 400)
      {
      digitalWrite(audio, HIGH);
      delayMicroseconds(NOTE_D2);
      digitalWrite(audio, LOW);
      delayMicroseconds(NOTE_D2);
      }
      Flex_1_value = analogRead(Flex_1);
 
      if(Flex_1_value >= 400)
      {
      digitalWrite(audio, HIGH);
      delayMicroseconds(NOTE_C2);
      digitalWrite(audio, LOW);
      delayMicroseconds(NOTE_C2);
      }
      
     Serial.println(Flex_5_value);
 }
 
  


