//MASTER

#include <SoftwareSerial.h>
#define NOTE_G2 2500
int Flex_1_value;
//int incoming_flex;
int Flex_1 = A0;

int audio = 8;
SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  pinMode(audio, OUTPUT);
  //digitalWrite(9, HIGH);
  Serial.begin(38400);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  
  if (BTSerial.available())
  {
    Serial.write(BTSerial.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  //incoming_flex = Serial.read();
  if (Serial.available())
  {
    /*
    digitalWrite(audio,HIGH);
    delayMicroseconds(NOTE_G2);
    digitalWrite(audio,LOW);
    delayMicroseconds(NOTE_G2);
    
    if(incoming_flex < 600)
    {
    digitalWrite(audio, LOW);
    }
    */
    BTSerial.write(Serial.read());
  }
//------------NOTES FOR LEFT HAND----------------
    Flex_1_value = analogRead(Flex_1);
 
      if(Flex_1_value >= 600)
      {
      digitalWrite(audio, HIGH);
      delayMicroseconds(NOTE_G2);
      digitalWrite(audio, LOW);
      delayMicroseconds(NOTE_G2);
      }

   
     
//--------------
/*
 if (Serial.available() > 0) 
 {
      Flex_2_value = Serial.read();
      
     
      
      if (Flex_2_value >= 600)
      {
      // read the incoming byte:
      digitalWrite(audio, HIGH);
      delayMicroseconds(NOTE_G2);
      digitalWrite(audio, LOW);
      delayMicroseconds(NOTE_G2);
      }
    
 }
 
 */
/*
     Serial.println(incoming_flex);
     Serial.print("\t");
     Serial.println(Flex_1_value);
     */
}


