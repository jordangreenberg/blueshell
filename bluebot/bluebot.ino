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
// END OF SENSOR VARIABLES

// GENERAL VARIABLES
int stepcount = 0;
#define RIGHT 1
#define LEFT 2
// END OF GENERAL VARIABLES

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
  Serial.println("Greetings bluebots");

  // Initialize motor speeds to 0
  set_speed(motor1_en, motor1_speed);
  set_speed(motor2_en, motor2_speed);
  set_speed(motor3_en, motor3_speed);
  set_speed(motor4_en, motor4_speed);

  // Set direction to forward
  forwardMotor = 1;
  change_heading(forwardMotor);

  // Take a sesnor measurement (so prevRight and prevLeft are initialized to current)
  isOriented();
  forwardMotor = clearestDirection();
  change_heading(forwardMotor);

  //PID
  // Setpoint is desired distance from wall to right side robot
  Setpoint = 8;
  SetpointReverse = 8;
  
  // turn PID on
  DirectPID.SetMode(AUTOMATIC);
  DirectPID.SetOutputLimits(0, 75);
  
  ReversePID.SetMode(AUTOMATIC);
  ReversePID.SetOutputLimits(0, 75);
  
} // end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  // NOTE: Might need to add delay to account or take it takes for robot to adjust motor speed

  // OVERALL PLAN:
  
  // Read sensors
  readSensors();
  sendSensorValues();

  // Scooch away from walls we are too close to
  scooch_scooch();

  // Change direction back to the forward direction
  change_heading(forwardMotor);

  // Read sensors again for localization
  readSensors();
  sendSensorValues();

  // Wait for MATLAB to respond with directions
  int matlabForwardMotor = getMatlabDirection();

  // If we got a valid newDirection, assign that and change directions
  if (matlabForwardMotor != -1) {
    forwardMotor = matlabForwardMotor;
    change_heading(forwardMotor);
  }

  // If we are approaching a wall in front, stop and reverse direction
  if (isForwardSafe(*forwardDistance) == false) {
    brake();
    forwardMotor = clearestDirection();
    change_heading(forwardMotor);
  }
  else {
    // Here is where we would put the obstacle avoidance logic 
    // i.e. should we change our heading/direction that we are moving?
  
    // If all 4 directions are clear - TODO: might want to remove backDistance as condition
    // Actually this condition might not even be necessary, maybe it's just forward clear or not clear??
    //if (isFourDirectionsClear(*forwardDistance, *rightDistance, *leftDistance, *backDistance)) {
      // Call controller to calculate correction
      //corrected_speed = pid_controller(*rightDistance, *leftDistance, *prevRight, *prevLeft);
    
      // Adjust speeds
      //adjustSpeeds(corrected_speed);
      
      // Move with corrected speeds
      drive_pid();

      delay(200); // MAYBE 1000?

      brake();

      // PUT BACK IS ORIENTED?
      // isOriented();

      brake();

      // Read the sensors again
      readSensors();
  
      // Look for a corridor
      //int corridor = new_corridor(*prevLeft, *leftDistance, *prevRight, *rightDistance, *backDistance, *forwardDistance);      
      //int corridor = findCorridor(*prevLeft, *leftDistance, *prevRight, *rightDistance, *backDistance, *forwardDistance);
  }
//// COMMENTING OUT THE REST OF THE CODE HERE
//      if (corridor == RIGHT || corridor == LEFT) {
//        //int cleared = true;
//        
//        // If we find a corridor, keep moving forward before changing the heading
//        while (clearance(*backDistance, corridorBackDistance, *forwardDistance, corridorFrontDistance) == false) {
//          readSensors();
//          if (isForwardSafe(*forwardDistance)) {
//            // Call controller to calculate correction
//            //corrected_speed = pid_controller(*rightDistance, *leftDistance, *prevRight, *prevLeft);
//          
//            // Adjust speeds
//            //adjustSpeeds(corrected_speed);
//            
//            // Move with corrected speeds
//            drive();
//
//            delay(200);
//
//            brake();
//
//          }
//          else {
//            
//            break;
//           /* // Reverse heading and break out of this loop - something went wrong
//            brake();
//            forwardMotor = reverseHeading(forwardMotor);
//            change_heading(forwardMotor);
//            cleared = false;
//            break;*/
//          } 
//        } // end of while (clearance(*backDistance, corridorBackDistance)) == false)
//
//        // Once we clear, change heading left or right to head down corridor
//        
//        forwardMotor = rotateHeading(corridor, forwardMotor);
//        Serial.print("Forward motor is now: ");
//        Serial.println(forwardMotor);
//        change_heading(forwardMotor); 
//        drive();
//        delay(200);
//        brake();
//        
//      } // end of if (corridor == RIGHT || corridor == LEFT)
//    //} // end of if all four directions are clear
//
//   // Maybe here we implement some rotating in case we get too close on either left/right walls - behind shouldn't be an issue
//    
//  } // end of else forwardDistance is unsafe
} // end of loop()
