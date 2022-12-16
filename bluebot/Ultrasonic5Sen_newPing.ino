//NewPing Library and Documentation can be found at
//http://playground.arduino.cc/Code/NewPing

#include <NewPing.h>

// TODO: NEED TO REASSIGN PIN NUMBERS
// Define pin assignments
#define TRIGGER_PIN  7
// #define TRIGGER_PIN2 8
#define ECHO_PIN1    2
#define ECHO_PIN2    3
#define ECHO_PIN3    4
#define ECHO_PIN4    5
#define ECHO_PIN5    6
#define ECHO_PIN6    8

#define MAX_DISTANCE 200

// SENSOR VARIABLESS
float distance1 = 0;
float distance2 = 0;
float distance3 = 0;
float distance4 = 0;
float distance5 = 0;
float distance6 = 0;

float prevDistance1;
float prevDistance2;
float prevDistance3;
float prevDistance4;
float prevDistance5;
float prevDistance6;

//int newDirection1 = 0;


float d1avg;
float d2avg;
float d3avg;
float d4avg;
float d5avg;
float d6avg;
// END of SENSOR VARIABLES

String d1;
String d2;
String d3;
String d4;
String d5;
String d6;

String comma = ",";

// Sensor objects
NewPing sonar1(TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN, ECHO_PIN4, MAX_DISTANCE);
NewPing sonar5(TRIGGER_PIN, ECHO_PIN5, MAX_DISTANCE);
NewPing sonar6(TRIGGER_PIN, ECHO_PIN6, MAX_DISTANCE);

void readSensors()
{
  prevDistance1 = distance1;
  prevDistance2 = distance2;
  prevDistance3 = distance3;
  prevDistance4 = distance4;
  prevDistance5 = distance5;
  prevDistance6 = distance6;

  distance1 = 0;
  distance2 = 0;
  distance3 = 0;
  distance4 = 0;
  distance5 = 0;
  distance6 = 0;

  int numAvg = 5;

  for (int i = 0; i < numAvg; i++) {
    //Serial.println("in for looop");

    delay(10);
    distance1 = distance1 + sonar1.ping_cm();
    //Serial.println(distance1);
    delay(10);
    distance2 = distance2 + sonar2.ping_cm();
    delay(10);
    distance3 = distance3 + sonar3.ping_cm();
    delay(10);
    distance4 = distance4 + sonar4.ping_cm();
    delay(10);
    distance5 = distance5 + sonar5.ping_cm();
    delay(10);
    distance6 = distance6 + sonar6.ping_cm();
    delay(10);

  }

  d1avg = distance1 / ((float)numAvg);
  //Serial.print("d1avg: ");
  //Serial.println(d1avg);
  d2avg = distance2 / ((float)numAvg);
  d3avg = distance3 / ((float)numAvg);
  d4avg = distance4 / ((float)numAvg);
  d5avg = distance5 / ((float)numAvg);
  d6avg = distance6 / ((float)numAvg);

  d1 = String(d1avg);
  //Serial.print("d1: ");
  //Serial.println(d1);
  d2 = String(d2avg);
  d3 = String(d3avg);
  d4 = String(d4avg);
  d5 = String(d5avg);
  d6 = String(d6avg);

  /*
    Serial.print("D1: ");
    Serial.print(d1avg);
    Serial.print(" | D5: ");
    Serial.println(d5avg);
    Serial.print("D2: ");
    Serial.print(d2avg);
    Serial.print(" | D4: ");
    Serial.print(d4avg);
  */
}

// send the sensor vaules to matlab

void sendSensorValues()
{
  //delay(10);
  char ack = 'n';
  while (ack != 'y') {
    Serial.println(d1 + comma + d2 + comma + d3 + comma + d4 + comma + d5 + comma + d6);
    digitalWrite(LED1, HIGH);
    if (Serial.available() > 0) {
      ack = Serial.read();
    }
    delay(50);

  }
  digitalWrite(LED1, LOW);
  //delay(10);
}

int getMatlabDirection()
{

  int newDirection = -1;


  while (true) {
  //for (int i = 0; i < 30; i++) {
    if (Serial.available() > 0) {
      char matlab_heading = Serial.read();
      //String matlab_heading = "90";
      //Serial.println("Matlab given heading: ");

      if (matlab_heading == '1') {    //0
        digitalWrite(LED1, HIGH);
        newDirection = 1;
        break;
        //Serial.println(newDirection);
      }
      else if (matlab_heading == '2') {   //90
        digitalWrite(LED2, HIGH);
        newDirection = 2;
        break;
        //Serial.println(newDirection);
      }
      else if (matlab_heading == '3') { //180
        digitalWrite(LED5, HIGH);
        newDirection = 3;
        break;
        //Serial.println(newDirection);
      }
      else if (matlab_heading == '4') {  //270
        digitalWrite(LED4, HIGH);
        newDirection = 4;
        break;
        //Serial.println(newDirection);
      }
      else if (matlab_heading == '0') {  //localized
        // Turn on localized LED
        newDirection1 = LOCALIZED;
        break;
      }
      else if (matlab_heading == '5') { //in loading zone
        // Turn off PID
        // Turn on LED
        newDirection2 = LOADING_ZONE;
        break;
      }
      else if (matlab_heading == '6') {   //cw
        // rotate clockwise
        newDirection = CLOCKWISE;
        break;
      }
      else if (matlab_heading == '7') { //ccw
        // rotate counter clockwise
        newDirection = COUNTER_CLOCKWISE;
        break;
      }
      else if (matlab_heading == '8') { //go to drop
        // Turn PID on
        newDirection5 = GO_TO_DROP;
        break;
      }
      else if (matlab_heading == '9') {  //start grabbing
        // Start rotating grabber
        newDirection6 = START_GRABBING;
        break;
      }
      else if (matlab_heading == 'a') {
        // Start rotating grabber to release block
        newDirection7 = START_DROPPING;
        break;
        // Turn on LED
      }
    }
  }
  return newDirection;
}


bool block_is_visible() {
  if (distance6 < (1 - tolerance_grabbing) * distance5) {
    return true;
  }
  else {
    return false;
  }
}
