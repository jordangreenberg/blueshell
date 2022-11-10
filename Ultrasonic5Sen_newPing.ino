//NewPing Library and Documentation can be found at
//http://playground.arduino.cc/Code/NewPing

#include <NewPing.h>
 
#define TRIGGER_PIN  22
#define ECHO_PIN1     11
#define ECHO_PIN2     9
#define ECHO_PIN3     10
#define ECHO_PIN4     3
//#define ECHO_PIN5     2

#define MAX_DISTANCE 200

int pingTime1 = 0;
int pingTime2 = 0;

float d1, d2, d3, d4, d5;
 
NewPing sonar1(TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN, ECHO_PIN4, MAX_DISTANCE);
//NewPing sonar5(TRIGGER_PIN, ECHO_PIN5, MAX_DISTANCE);
 
void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  
  //if (Serial.available()>0)
  //{
    //char ch = Serial.read();
    //if (ch == 'r')
    //{  
       delay(30);
       d1 = sonar1.ping_cm();
       delay(30);
       d2 = sonar2.ping_cm();
       delay(30);
       d3 = sonar3.ping_cm();
       delay(30);
       d4 = sonar4.ping_cm();
       delay(30);
//       d5 = sonar5.ping_cm();
       
       Serial.print("D1: ");
       Serial.print(d1);
       Serial.print(" D2: ");
       Serial.println(d2);
       Serial.print(" D3: ");
       Serial.print(d3);
       Serial.print(" D4: ");
       Serial.println(d4);
//       Serial.print(" D5: ");
//       Serial.println(d5);
    //}
  //}
}
