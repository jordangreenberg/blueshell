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
  
  // Read each sensor 30 milliseconds apart
  delay(30);
  distance1 = sonar1.ping_cm();
  delay(30);
  distance2 = sonar2.ping_cm();
  delay(30);
  distance3 = sonar3.ping_cm();
  delay(30);
  distance4 = sonar4.ping_cm();
  delay(30);
  distance5 = sonar5.ping_cm();
  delay(30);

  //if (Serial.available())
  //{
    // Print sensor measurements
    /*
    Serial.print(" Left: ");
    Serial.print(distance2);
    Serial.print(" Right: ");
    Serial.println(distance4); 
    Serial.print(" Front: ");
    Serial.print(distance1);
    Serial.print(" Back: ");
    Serial.println(distance3);
    Serial.println(" ");
    */
  //}
}

void sendSensorValues()
{
  if (Serial.available()>0) {
    Serial.print(distance1);
    Serial.print(",");
    Serial.print(distance2);
    Serial.print(",");
    Serial.print(distance3);
    Serial.print(",");
    Serial.println(distance4);
  }
}

int getMatlabDirection()
{
  String matlabInstruction;
  int newDirection = -1;

  while (true) {
    if (Serial.available()>0) {
      matlabInstruction = Serial.readString();

      if (matlabInstruction == "0") {
        newDirection = 1;
        break;
      }
      else if (matlabInstruction == "90") {
        newDirection = 2;
        break;
      }
      else if (matlabInstruction == "180") {
        newDirection = 3;
        break;
      }
      else if (matlabInstruction == "270") {
        newDirection = 4;
        break;
      }
    }
    else {
      break;
    }
  }

  return newDirection;
}
