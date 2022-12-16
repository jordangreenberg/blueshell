# include <PID_v1.h>
// Define global variables
// MOTOR VARIABLES
int motor1_en = 12;
int motor1_in1 = 34;
int motor1_in2 = 36;
int motor1_speed = 0;
bool motor1_forward = true;

int motor2_en = 9;
int motor2_in1 = 22;
int motor2_in2 = 24;
int motor2_speed = 0;
bool motor2_forward = true;

int motor3_en = 11;
int motor3_in1 = 30;
int motor3_in2 = 32;
int motor3_speed = 0;
bool motor3_forward = true;

int motor4_en = 10;
int motor4_in1 = 26;
int motor4_in2 = 28;
int motor4_speed = 0;
bool motor4_forward = true;

int motor5_en = 13;
int motor5_in1 = 39;
int motor5_in2 = 41;
int eat_speed = 120;

double corrected_speed = 0;
int * rightSpeed;
int * leftSpeed;
int * frontSpeed;
int * backSpeed;
int * right_en;
int * front_en;
int * back_en;
int * left_en;
int forwardMotor;
// END of MOTOR VARIABLES

// SENSOR VARIABLES
float * rightDistance;
float * leftDistance;
float * prevRight;
float * prevLeft;
float * forwardDistance;
float * backDistance;
float * five_distance;
float corridorBackDistance = 0;
float corridorFrontDistance = 0;

int newDirection1 = 0;      //// set to 5 for localized, for picking up block, set this to zero
int newDirection2 = 0;      //// keep as 0 for localized and heading to loading zone
int newDirection3 = 0;
int newDirection4 = 0;
int newDirection5 = 9;    /// set to 9 for drop off to drop zone ** calibrated for drop zone 1
int newDirection6 = 0;    ///set to 10 for blocking
int newDirection7 = 0;
// END OF SENSOR VARIABLES

// GENERAL VARIABLES
int stepcount = 0;
bool pid_on = true;
bool grabbing = false;    // should be false unless you are grabbing the block, then set to true
bool dropping = false;
const double tolerance_grabbing = 0.1;
#define RIGHT 1
#define LEFT 2
#define LOCALIZED 5
#define LOADING_ZONE 6
#define CLOCKWISE 7
#define COUNTER_CLOCKWISE 8
#define GO_TO_DROP 9
#define START_GRABBING 10
#define START_DROPPING 11
// END OF GENERAL VARIABLES

// LEDS
#define LED1         50
#define LED2         42
#define LED3         44
#define LED4         46
#define LED5         52
// END OF LEDS

double Setpoint, SetpointReverse, InputDirect, OutputDirect;
double InputReverse, OutputReverse;

// Tune kp THEN kd, THEN ki as needed. May need to have seperate k values for direct/reverse controllers
double kp = 0.3;
double ki = 1.9;
double kd = 1.9;

// Direct and reverse PIDs to make adjustment in each direction

PID DirectPID(&InputDirect, &OutputDirect, &Setpoint, kp, ki, kd, DIRECT);
PID ReversePID(&InputReverse, &OutputReverse, &SetpointReverse, kp, ki, kd, REVERSE);
// & indicates variable value passed to function may change by function

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("Greetings bluebots");

  // Initialize motor speeds to 0
  set_speed(motor1_en, motor1_speed);
  set_speed(motor2_en, motor2_speed);
  set_speed(motor3_en, motor3_speed);
  set_speed(motor4_en, motor4_speed);

  // Set direction to forward
  forwardMotor = 1;
  change_heading(forwardMotor);

  // Take a sesnor measurement (so prevRight and prevLeft are initialized to current)
  //  Serial.println("Before orienting");
  //  while(true) {
  //    isOriented();
  //  }

  //forwardMotor = clearestDirection();
  //change_heading(forwardMotor);

  //PID
  // Setpoint is desired distance from wall to right side robot
  Setpoint = 8;
  SetpointReverse = 8;

  // turn PID on
  DirectPID.SetMode(AUTOMATIC);
  DirectPID.SetOutputLimits(0, 75);

  ReversePID.SetMode(AUTOMATIC);
  ReversePID.SetOutputLimits(0, 75);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

} // end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  // NOTE: Might need to add delay to account or take it takes for robot to adjust motor speed

  // OVERALL PLAN:

  // Read sensors

//  if ((newDirection1 == 5) && (newDirection2 != 6)) {
//    scooch_scooch();
//    Serial.println("69");
//  }
  if (newDirection5 == 9){
    scooch_scooch();
    Serial.println("13");
  }
//  else if (newDirection6 == 10){
////////////////    Serial.println("new direction is 10");
//////////////////    scooch_scooch();
/////////////////    readSensors();
//////////////////    Serial.println("read sensors");
/////////////////    sendSensorValues();
//    block_motor_onload();
//    forwardMotor = 1;
//    Serial.println("start");
//    delay(2000);
//    rotate_counter_clockwise();
//    delay(2100);
//    brake();
//    change_heading(forwardMotor);
//    drive();
//    delay(1000);
//    brake();
//    block_motor_offload();
//  }
  else {
    readSensors();
    Serial.println("read sensors");
    sendSensorValues();
    scooch_scooch();
    readSensors();
    sendSensorValues();
 }

  //readSensors();
  //sendSensorValues();

  // Scooch away from walls we are too close to
  //scooch_scooch();

  // Change direction back to the forward direction
  // change_heading(forwardMotor);

  // Read sensors again for localization
  //readSensors();
  //sendSensorValues();

  // Wait for MATLAB to respond with directions
  int matlabForwardMotor = getMatlabDirection();
  Serial.println(matlabForwardMotor);

  // If we got a valid newDirection, assign that and change directions
  if (matlabForwardMotor != -1) {
    if (matlabForwardMotor >= 1 && matlabForwardMotor <= 4) {
      digitalWrite(LED1, HIGH);
      forwardMotor = matlabForwardMotor;
      change_heading(forwardMotor);
    }
    else if (matlabForwardMotor == LOCALIZED) {
      // Turn on localized LED
      digitalWrite(LED1, HIGH);
    }
    else if (matlabForwardMotor == LOADING_ZONE) {
      // Turn off PID
      pid_on = false;
      // Turn on LED
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    }
    else if (matlabForwardMotor == CLOCKWISE) {
      // rotate clockwise
      Serial.println("rotating cw");
      rotate_clockwise();
      delay(150);
      brake();
    }
    else if (matlabForwardMotor == COUNTER_CLOCKWISE) {
      // rotate counter clockwise
      Serial.println("rotating ccw");
      rotate_counter_clockwise();
      delay(150);
      brake();
    }
    else if (matlabForwardMotor == GO_TO_DROP) {
      // Turn PID on
      pid_on = true;
    }
    else if (matlabForwardMotor == START_GRABBING) {
      grabbing = true;
    }
    else if (matlabForwardMotor == START_DROPPING) {
      dropping = true;
      // Turn on LED
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
    }
    digitalWrite(LED3, LOW);
  }
  else {
    digitalWrite(LED3, HIGH);
  }


  // If we are approaching a wall in front, stop and reverse direction
  if (isForwardSafe(*forwardDistance) == false) {
    brake();
    Serial.println("braking");
    // forwardMotor = clearestDirection();
    // change_heading(forwardMotor);
  }
  else if (grabbing) {
    // Scooch to pickup block
    Serial.println("in grabbing loop");
    int scooch_count = 0;
    while (block_is_visible()) { // block is visible
      change_heading(4);
      drive();
      delay(50);
      brake();
      scooch_count++;
    }

    // Pickup the block
    block_motor_onload();

    // Scooch back
    for (int i = 0; i < scooch_count; i++) {
      //Serial.println("scooch back");
      change_heading(2);
      drive();
      delay(50);
      brake();
    }
    // Tell Matlab we have the block
    Serial.println("11");
    grabbing = false;
  }
  else if (dropping) {
    block_motor_offload();
  }
  else {
    //Serial.println("We made it to the bottom");
    // Move with corrected speeds (if Matlab is telling us to move)
    if (matlabForwardMotor >= 1 && matlabForwardMotor <= 4) {
      if (pid_on) {
        //Serial.println("Drive PID");
        drive_pid();
      }
      else {
        drive();
      }

      delay(1000); // MAYBE 1000?

      brake();

      // Safety scooch
      scooch_scooch();
      change_heading(forwardMotor);
    } // end of if matlab is telling to go in a direction
  } // end of if forward direction is safe
} // end of loop()
