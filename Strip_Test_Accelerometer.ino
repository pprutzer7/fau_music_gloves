#include "CurieIMU.h"


//Fingers 1 and 2 variables
int Finger_1;
/*
int Finger_3;
int Finger_4;
int Thumb;
*/

//Analog inputs for flex sensors
int analogPin = A0;

//Speaker out at pin ~6 OR simulated outputs (LEDs)
int LED1 = 4;
int LED2 = 7;
int LED3 = 2;


int lastOrientation = - 1; // previous orientation (for comparison)

//Button represents thumb on digital input pin 2
//int Button = 2;
//Checks for state of thumb or button as either HIGH or LOW
//int count = 0;

void setup() 
{
  //Setting speaker variable Audio to output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  //configuring thumb as an input (in this examples I'm using a dip-switch)
  //pinMode(Button, INPUT);

  //initialize device
  CurieIMU.begin();
  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  
  Serial.begin(9600);
}

void loop() 
{
  int orientation = - 1;   // the board's orientation
  // read accelerometer:
  int x = CurieIMU.readAccelerometer(X_AXIS);
  int y = CurieIMU.readAccelerometer(Y_AXIS);
  int z = CurieIMU.readAccelerometer(Z_AXIS);

  // calculate the absolute values, to determine the largest
  int absX = abs(x);
  int absY = abs(y);
  int absZ = abs(z);

  
   Finger_1 = analogRead(analogPin);
   //calibrates reading to baseline 180 degrees. maximum value is 240. 60 degrees of range.
   Finger_1 = (Finger_1/4) - 15;
  
  /*
   * Finger_3 = analogRead(analogPin_2);
   * Finger_4 = analogRead(analogPin_3);
   * Thumb = analogRead(analogPin_4);
   */

  //count = digitalRead(Button);

 /*
  * The Finger_1 and Finger_2 values below were based on the Potentiometer and photoresistor I was using.
  * Those values will change based off of the flex sensors.
  */

  //30 degree bend
  if((Finger_1 >= 210) && (Finger_1 <= 225)) //&& (count == HIGH))
  {
    digitalWrite(LED2, HIGH);
    
  }
  //maximum bend at 60 degrees
  else if (Finger_1 >= 240)// && (count == LOW))
  {
    digitalWrite(LED1, HIGH);
   
  }
  else
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
 
  //if the user raises their hand, the octave is switched
  if ((absZ < absX) && (absZ < absY)) 
  {
  
    // base orientation on Z
    if ((z < 0) && (Finger_1 >= 240))
    {
      orientation = 0;  
      digitalWrite(LED3, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
    } 
    else 
    {
      orientation = 1;
    }
    
  }
  //if the user lowers their hand the octave is switched
   else if ((absY < absX) && (absY < absZ)) 
  {
    // base orientation on Y
    if (y > 0) 
    {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      orientation = 2;
    } 
    else 
    {
      
      orientation = 3;
    }
  }
   
  else 
  {
    // base orientation on X
    if (x < 0) 
    {
      orientation = 4;
    } 
    else 
    {
      orientation = 5;
    }
  }
  
  Serial.println(absZ);
}

