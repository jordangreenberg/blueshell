
double rightDistance;     // sensor data
double leftDistance;      // sensor data

double error;
double prevError;
double sumError;
double rateError;

int kp = 1;
int ki = 2;
int kd = 3;

unsigned long currTime = millis();
unsigned long prevTime = 0;
double elapsedTime;

double correction;

/*
void setup() {
   // put your setup code here, to run once: 
*/

/*
void loop() {
  // put your main code here, to run repeatedly:
  
  elapsedTime = currTime - prevTime;

  error = rightDistance - leftDistance;                 // want distances equal so difference in distance should be 0
  sumError += error * elapsedTime;                      // cumulative error for integral controller 
  rateError = (error - prevError) / elapsedTime;        // rate error for derivative controller

  correction = kp*error + ki*sumError + kd*rateError;   // end result of controller to be used to adjust motors

  // if error +ve robot is moving to the right; if error is -ve moving left
  // therefore want to speed up left motor/slow right motor if error is positive and vice versa

  // rightAdjustedSpeed -= correction;        // adjust right side motor speed
  // leftAdjustedSpeed += correction;         // adjust left side motor speed


prevError = error;
prevTime = currTime;

}
*/
