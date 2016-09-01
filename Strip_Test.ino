//Fingers 1 and 2 variables
int Finger_1;
int angle;
/*
int Finger_3;
int Finger_4;
int Thumb;
*/

//Analog inputs for flex sensors
int analogPin = A0;

//Speaker out at pin ~6
int LED1 = 11;
int LED2 = 8;

//Button represents thumb on digital input pin 2
int Button = 2;
//Checks for state of thumb or button as either HIGH or LOW
int count = 0;

void setup() {
  //Setting speaker variable Audio to output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  //configuring thumb as an input (in this examples I'm using a dip-switch)
  pinMode(Button, INPUT);
  Serial.begin(9600);
}

void loop() {
   Finger_1 = analogRead(analogPin);
   //calibrates reading to baseline 180 degrees. maximum value is 240. 60 degrees of range.
   Finger_1 = (Finger_1/4) - 15;
  
  /*
   * Finger_3 = analogRead(analogPin_2);
   * Finger_4 = analogRead(analogPin_3);
   * Thumb = analogRead(analogPin_4);
   */

  count = digitalRead(Button);

 /*
  * The Finger_1 and Finger_2 values below were based on the Potentiometer and photoresistor I was using.
  * Those values will change based off of the flex sensors.
  */

  //30 degree bend
  if((Finger_1 >= 210) && (Finger_1 <= 220) && (count == HIGH))
  {
    digitalWrite(LED2, HIGH);
    
  }
  //maximum bend
  else if ((Finger_1 >= 241) && (count == LOW))
  {
    digitalWrite(LED1, HIGH);
   
  }
  else
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
   
  }
  
  Serial.println(Finger_1);
}

