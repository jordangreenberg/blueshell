//NewPing Library and Documentation can be found at
//http://playground.arduino.cc/Code/NewPing

#include <NewPing.h>

// TODO: NEED TO REASSIGN PIN NUMBERS
// Define pin assignments
#define TRIGGER_PIN  7
#define ECHO_PIN1    2
#define ECHO_PIN2    3
#define ECHO_PIN3    4
#define ECHO_PIN4    5

#define MAX_DISTANCE 200

// SENSOR VARIABLES
float distance1;
float distance2;
float distance3;
float distance4;
// END of SENSOR VARIABLES

// Sensor objects
NewPing sonar1(TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN, ECHO_PIN4, MAX_DISTANCE);
 
void readSensors() 
{
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

  //if (Serial.available())
  //{
    // Print sensor measurements
    //Serial.print(" D1: ");
    //Serial.print(distance1);
    Serial.print(" D2: ");
    Serial.print(distance2);
    //Serial.print(" D3: ");
    //Serial.print(distance3);
    Serial.print(" D4: ");
    Serial.println(distance4); 
  //}
}
