// Define global variables
// MOTOR VARIABLES
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

double corrected_speed = 0;
int * rightSpeed;
int * leftSpeed;
int * right_en;
int * left_en;
int forwardMotor;
// END of MOTOR VARIABLES

// SENSOR VARIABLES
float * rightDistance;
float * leftDistance;
// END OF SENSOR VARIABLES

// Notes

// When implementing this for four wheels, I think we focus on activating two wheels at a time
// The other two wheels can be "passive" and drag along
// This should allow us to "spidercrawl" (obviously we will have to test)


void setup() {
  // put your setup code here, to run once:
  
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

  // Take a sesnor measurement (so prevRight and prevLeft are initialized to current)
  readSensors();

  // TODO: Determine which way we are going - should we orient first?
  forwardMotor = 1;
  change_heading(forwardMotor);
    
  // Initialize controller
  init_controller(*rightDistance, *leftDistance);
  
} // end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  // NOTE: Might need to add delay to account or take it takes for robot to adjust motor speed

  // OVERALL PLAN:
  
  // Read sensors
  readSensors();

  // Here is where we would put the obstacle avoidance logic 
  // i.e. should we change our heading/direction that we are moving?
  
  // Call controller to calculate correction
  corrected_speed = pid_controller(*rightDistance, *leftDistance);

  // Adjust speeds
  adjustSpeeds(corrected_speed);
  
  // Move with corrected speeds
  drive();

  // KEEPING THE BELOW CODE FOR NOW TO TEST MOTORS
  /*
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
  */
} // end of loop()
