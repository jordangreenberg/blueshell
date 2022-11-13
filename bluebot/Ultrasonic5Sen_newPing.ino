//NewPing Library and Documentation can be found at
//http://playground.arduino.cc/Code/NewPing

#include <NewPing.h>

// Define pin assignments
#define TRIGGER_PIN  7
#define ECHO_PIN1    2
#define ECHO_PIN2    3
#define ECHO_PIN3    4
#define ECHO_PIN4    5

#define MAX_DISTANCE 200

// SENSOR VARIABLES
float distance1 = 0;
float distance2 = 0;
float distance3 = 0;
float distance4 = 0;

float prevDistance1;
float prevDistance2;
float prevDistance3;
float prevDistance4;
// END of SENSOR VARIABLES

// Sensor objects
NewPing sonar1(TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN, ECHO_PIN4, MAX_DISTANCE);
 
void readSensors() 
{
  prevDistance1 = distance1;
  prevDistance2 = distance2;
  prevDistance3 = distance3;
  prevDistance4 = distance4;
  
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

  if (Serial.available())
  {
    // Print sensor measurements
    //Serial.print(" D1: ");
    //Serial.print(distance1);
    Serial.print(" D2: ");
    Serial.print(distance2);
    //Serial.print(" D3: ");
    //Serial.print(distance3);
    Serial.print(" D4: ");
    Serial.println(distance4); 
  }
}
