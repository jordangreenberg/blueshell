# include <PID_v1.h>

double Setpoint, InputDirect, OutputDirect;
double InputReverse, OutputReverse;

double rightDistance;
double rightMotorSpeed;

// Tune kp THEN kd, THEN ki as needed. May need to have seperate k values for direct/reverse controllers
double kp = 1;
double ki = 0; 
double kd = 0; 


// Direct and reverse PIDs to make adjustment in each direction
PID DirectPID(&InputDirect, &OutputDirect, &Setpoint, kp, ki, kd, DIRECT); 
PID ReversePID(&InputReverse, &OutputReverse, &Setpoint, kp, ki, kd, REVERSE);
// & indicates variable value passed to function may change by function


void setup() {
  // put your setup code here, to run once:

// Setpoint is desired distance from wall to right side robot
Setpoint = 10;

// turn PID on
DirectPID.SetMode(AUTOMATIC);
DirectPID.SetOutputLimits(0, 55);

ReversePID.SetMode(AUTOMATIC);
ReversePID.SetOutputLimits(0, 55);
}

void loop() {
  // put your main code here, to run repeatedly:

if ( 4 =< rightDistance <= 20 )
{
  if (rightDistance == Setpoint)
    {
    //Do nothing/no changes & motors remain unchanged
    Serial.print("  Right distance = ");
    Serial.print(rightDistance);
    Serial.println();
    }
  
  if (rightDistance < Setpoint)
    {
    InputDirect = rightDistance;
    DirectPID.Compute();
    rightMotorSpeed += OutputDirect; 
  
    Serial.print("   OutputDirect = ");
    Serial.print(OutputDirect);
    Serial.print("   rightMotorSpeed = ");
    Serial.print(rightMotorSpeed);
    Serial.print("   Right distance = ");
    Serial.print(rightDistance);
    Serial.println();
    }
  
  if (rightDistance > Setpoint)
    {
    InputReverse = rightDistance;
    ReversePID.Compute();
    rightMotorSpeed -= OutputDirect; 
  
    Serial.print("   OutputReverse = ");
    Serial.print(OutputReverse);
    Serial.print("   rightMotorSpeed = ");
    Serial.print(rightMotorSpeed);
    Serial.print("   Right distance = ");
    Serial.print(rightDistance);
    Serial.println();
    }
  }
}
