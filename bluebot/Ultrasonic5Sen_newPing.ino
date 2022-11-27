//NewPing Library and Documentation can be found at
//http://playground.arduino.cc/Code/NewPing

// TODO: Add 5th sensor

#include <NewPing.h>

// Define pin assignments
#define TRIGGER_PIN  7
#define ECHO_PIN1    2
#define ECHO_PIN2    3
#define ECHO_PIN3    4
#define ECHO_PIN4    5
#define ECHO_PIN5    6

#define MAX_DISTANCE 200

// SENSOR VARIABLES
float distance1 = 0;
float distance2 = 0;
float distance3 = 0;
float distance4 = 0;
float distance5 = 0;

float prevDistance1;
float prevDistance2;
float prevDistance3;
float prevDistance4;
float prevDistance5;
// END of SENSOR VARIABLES

// Sensor objects
NewPing sonar1(TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN, ECHO_PIN4, MAX_DISTANCE);
NewPing sonar5(TRIGGER_PIN, ECHO_PIN5, MAX_DISTANCE);
 
void readSensors() 
{
  prevDistance1 = distance1;
  prevDistance2 = distance2;
  prevDistance3 = distance3;
  prevDistance4 = distance4;
  prevDistance5 = distance5;

  distance1 = 0;
  distance2 = 0;
  distance3 = 0;
  distance4 = 0;
  distance5 = 0;
  
for (int i = 0; i < numAvg; i++) {
    //Serial.println("in for looop");

    delay(30);
    distance1 = distance1 + sonar1.ping_cm();
    //Serial.println(distance1);
    delay(30);
    distance2 = distance2 + sonar2.ping_cm();
    delay(30);
    distance3 = distance3 + sonar3.ping_cm();
    delay(30);
    distance4 = distance4 + sonar4.ping_cm();
    delay(30);
    distance5 = distance5 + sonar5.ping_cm();
    delay(30);

  }

  d1avg = distance1 / ((float)numAvg);
  //Serial.print("d1avg: ");
  //Serial.println(d1avg);
  d2avg = distance2 / ((float)numAvg);
  d3avg = distance3 / ((float)numAvg);
  d4avg = distance4 / ((float)numAvg);
  d5avg = distance5 / ((float)numAvg);

  d1 = String(d1avg);
  //Serial.print("d1: ");
  //Serial.println(d1);
  d2 = String(d2avg);
  d3 = String(d3avg);
  d4 = String(d4avg);
  d5 = String(d5avg);

}

// send the sensor vaules to matlab

void sendSensorValues()
{

  delay(10);
  Serial.println(d1 + comma + d2 + comma + d3 + comma + d4 + comma + d5);
  delay(10);

}

int getMatlabDirection()
{

  int newDirection = -1;

  //while (true) {
  if (Serial.available() > 0) {
    matlab_heading = Serial.read();
    //Serial.println("Matlab given heading: ");

    if (matlab_heading == "0") {
      newDirection = 1;
      //Serial.println(newDirection);

    }
    else if (matlab_heading == "90") {
      newDirection = 2;
      //Serial.println(newDirection);

    }
    else if (matlab_heading == "180") {
      newDirection = 3;
      //Serial.println(newDirection);

    }
    else if (matlab_heading == "270") {
      newDirection = 4;
      //Serial.println(newDirection);
    }
  }
  return newDirection;
}
