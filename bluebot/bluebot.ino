// Define global variables

// MOTORS
int motor1_en = 9;
int motor1_in1 = 22;
int motor1_in2 = 24;
int motor1_speed = 0;
bool motor1_forward = true;

int motor2_en = 10;
int motor2_in1 = 26;
int motor2_in2 = 28;
int motor2_speed = 0;
bool motor2_forward = true;

int motor3_en = 11;
int motor3_in1 = 30;
int motor3_in2 = 32;
int motor3_speed = 0;
bool motor3_forward = true;

int motor4_en = 12;
int motor4_in1 = 34;
int motor4_in2 = 36;
int motor4_speed = 0;
bool motor4_forward = true;


char val = 0; //holds ascii from serial line

// MOTOR CONTROLLER FUNCTIONS /////////////////////////////////
// Code adapted from MC_PWM_clean.ino provided on Quercus
// Potentially for Uno and not Mega, will have to test

// Set speed of a motor given the motor enable pin and the desired speed
void set_speed(int motor_en, int desired_speed)
{
  // Safety check to ensure speed is valid
  if (desired_speed >= 0 && desired_speed <= 255)
  {
    analogWrite(motor_en, desired_speed);
  }
}

// Change direction of a motor given the motor input pins
// Will probably have to adapt because each motor might be different
void change_direction(int motor_forward, int motor_in1, int motor_in2)
{
  if (motor_forward) // if forward
  {
    digitalWrite(motor_in1, HIGH);
    digitalWrite(motor_in2, LOW);
  }
  else
  {
    digitalWrite(motor_in1, LOW);
    digitalWrite(motor_in2, HIGH);
  }
}

/*
//Speeds are between -32 and 32
void set_speedA(signed char speed) 
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
*/
// Notes

// When implementing this for four wheels, I think we focus on activating two wheels at a time
// The other two wheels can be "passive" and drag along
// This should allow us to "spidercrawl" (obviously we will have to test)

// This code will also have to be adapted to use L298N drivers (I don't think it does)

void setup() {
  // put your setup code here, to run once:
  /*
  // Sample code from quercus
  Serial.begin(9600);
  Serial.println("Greetings bluebots");
  set_speedA(i);
  set_speedB(j);
  // End of sample code from quercus
  */
  Serial.begin(9600);
  Serial.println("Greetings bluebots");

  // Initialize motor speeds to 0
  set_speed(motor1_en, motor1_speed);
  set_speed(motor2_en, motor2_speed);
  set_speed(motor3_en, motor3_speed);
  set_speed(motor4_en, motor4_speed);

  // Initialize motor directions to forward
  change_direction(motor1_forward, motor1_in1, motor1_in2);
  change_direction(motor2_forward, motor2_in1, motor2_in2);
  change_direction(motor3_forward, motor3_in1, motor3_in2);
  change_direction(motor4_forward, motor4_in1, motor4_in2);
  
  
} // end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  // This code will control two motors that are setup in left/right configuration
  // 'w' (forward), 'a' (left), 's' (backward), 'd' (right), 'k' (stop) can be input to control the motors

  if (Serial.available())
  {
    val = Serial.read();
    Serial.println(val); // print out input
    if (val == 'w')
      {
        motor1_speed = motor1_speed + 8;
        motor2_speed = motor2_speed + 8;
        set_speed(motor1_en, motor1_speed);
        set_speed(motor2_en, motor2_speed);
      }
      else if(val == 's')
      {
        motor1_speed = motor1_speed - 8;
        motor2_speed = motor2_speed - 8;
        set_speed(motor1_en, motor1_speed);
        set_speed(motor2_en, motor2_speed);
      }
      else if(val == 'd')
      {
        motor1_speed = motor1_speed + 8;
        motor2_speed = motor2_speed - 8;
        set_speed(motor1_en, motor1_speed);
        set_speed(motor2_en, motor2_speed);
      }
      else if(val == 'a')
      {
        motor1_speed = motor1_speed - 8;
        motor2_speed = motor2_speed + 8;
        set_speed(motor1_en, motor1_speed);
        set_speed(motor2_en, motor2_speed);
      }
      else if(val == 'k')
      {
        motor1_speed = 0;
        motor2_speed = 0;
        set_speed(motor1_en, motor1_speed);
        set_speed(motor2_en, motor2_speed);
      }
  } // end of if (Serial.available())
} // end of loop()
