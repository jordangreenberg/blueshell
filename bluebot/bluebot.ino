char val = 0; //holds ascii from serial line

signed char i = 0; // motor 1 speed - probably rename this
signed char j = 0; // motor 2 speed - probably rename this

int trigPin = 13; 
int echoPin1 = ?;
int echoPin2 = ?;
int echoPin3 = ?;
int echoPin4 = ?;

int pingTime1 = 0;
int pingTime2 = 0;
int pingTime3 = 0;
int pingTime4 = 0;
float distance1= 0;
float distance2 = 0;
float distance3 = 0;
float distance4 = 0;

//int motorpin = ?; ***
//int motorspeed = 0; ***
//int motordirection = 0;


// MOTOR CONTROLLER FUNCTIONS /////////////////////////////////
// Code adapted from MC_PWM_clean.ino provided on Quercus
// Potentially for Uno and not Mega, will have to test
//Speeds are between -32 and 32
void set_speedA(signed char speed) // live laugh love
{
  if((speed > -128) && (speed < 128))
  {
     analogWrite(9, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     analogWrite(10, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     TCCR1A |= B00110000;  //invert PWM output - using timer interrupts, will have to look more into this
  }
}
void set_speedB(signed char speed)
{
  if((speed > -128) && (speed < 128))
  {
     analogWrite(5, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     analogWrite(6, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     TCCR0A |= B00110000;  //invert PWM output - using timer interrupts, will have to look more into this
  }
}
// END OF MOTOR CONTROLLER FUNCTIONS //////////////////////////

// Notes

// When implementing this for four wheels, I think we focus on activating two wheels at a time
// The other two wheels can be "passive" and drag along
// This should allow us to "spidercrawl" (obviously we will have to test)

// This code will also have to be adapted to use L298N drivers (I don't think it does)

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);

  Serial.begin(9600);
  Serial.println("Greetings bluebots");
  set_speedA(i);
  set_speedB(j);

} // end of setup()

void loop() {
  // put your main code here, to run repeatedly:

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2000);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pingTime1 = pulseIn (echoPin1, HIGH);
    //Serial.println(pingTime1);
    delay(500);
    distance1 = pingTime1 * 0.5 * 0.034; 
    //Serial.println(distance1);
    delay(500);

    pingTime2 = pulseIn (echoPin2, HIGH);
    //Serial.println(pingTime2);
    delay(500);
    distance2 = pingTime2 * 0.5 * 0.034; 
    //Serial.println(distance2);
    delay(500);

    pingTime3 = pulseIn (echoPin3, HIGH);
    //Serial.println(pingTime3);
    delay(500);
    distance3 = pingTime3 * 0.5 * 0.034; 
    //Serial.println(distance3);
    delay(500);

    pingTime4 = pulseIn (echoPin4, HIGH);
    //Serial.println(pingTime4);
    delay(500);
    distance4 = pingTime4 * 0.5 * 0.034; 
    //Serial.println(distance4);
    delay(500);

/*
Move fubction

    if (distance1 > ) {
      motorspeed/direction(angle)= distance/37.0*255;     # operating range of ultrasonic sensor stopped at 37
      Serial.println(LEDb);
      analogWrite(motorpin, LEDb);
    }
    else {
      analogWrite(motorpin, 0);

    }
*/

  // This code will control two motors that are setup in left/right configuration
  // 'w' (forward), 'a' (left), 's' (backward), 'd' (right), 'k' (stop) can be input to control the motors
  if (Serial.available())
  {
    val = Serial.read();
    Serial.println(val); // print out input
    if (val == 'w')
      {
        i = i + 8;
        j = j + 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 's')
      {
        i = i - 8;
        j = j - 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 'd')
      {
        i = i + 8;
        j = j - 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 'a')
      {
        i = i - 8;
        j = j + 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 'k')
      {
        i = 0;
        j = 0;
        set_speedA(i);
        set_speedB(j);
      }
  } // end of if (Serial.available())
} // end of loop()
