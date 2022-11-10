
double rightDistance;     // sensor data
double leftDistance;      // sensor data
double prevRight;
double prevLeft;

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
double rightAdjustedSpeed;
double leftAdjustedSpeed;
double minAdjust = 0;
double maxAdjust = 255;

// constrain (rightAdjustedSpeed, minAdjust, maxAdjust);
// constrain (leftAdjustedSpeed, minAdjust, maxAdjust);


void setup() {
   // put your setup code here, to run once: 
}

void loop() {
  // put your main code here, to run repeatedly:

   elapsedTime = currTime - prevTime;

    
  // *** may want to adjust multiplyer for corridor checks from 1.1 to something else
  
  if (rightDistance < prevRight*1.10 && rightDistance > prevRight*0.90) {               
    // if current distance increased from prev measurement by more than 10%, new corridor detected
    // if current distance decreased from prev measurement by more than 10%, current corridor narrowed (loading zone to corridor)
    // when the current hallway changed revealing new paths, we will take the error measurement from the left side

    error = rightDistance - prevRight;                    // want right distance measurements to remain constant
    sumError += error * elapsedTime;                      // cumulative error for integral controller 
    rateError = (error - prevError) / elapsedTime;        // rate error for derivative controller

    // if the error is positive that means the robot is moving further from the right wall (it is drifting left)
    // therefore we need to speed up left motor and slow right motor and vice versa
  
    correction = kp*error + ki*sumError + kd*rateError;   // end result of controller to be used to adjust motors
  
    // if error +ve robot is moving to the right; if error is -ve moving left
    // therefore want to speed up left motor/slow right motor if error is positive and vice versa
  
    // rightAdjustedSpeed -= correction;        // adjust right side motor speed
    // leftAdjustedSpeed += correction;         // adjust left side motor speed
  }

  else if (leftDistance < prevLeft*1.10 && leftDistance > prevLeft*0.90) {       
    // in case right side has a path change, now using the left side as the error calculator
    // if current distance increased from prev measurement by more than 10%, new corridor detected
    // if current distance decreased from prev measurement by more than 10%, current corridor narrowed (loading zone to corridor)
    // when the current hallway changed revealing new paths on both sides, robot must stop to recalculate new distance measurements


    error = leftDistance - prevLeft;                      // want left distance measurements to remain constant
    sumError += error * elapsedTime;                      // cumulative error for integral controller 
    rateError = (error - prevError) / elapsedTime;        // rate error for derivative controller

    // if the error is positive that means the robot is moving further from the left wall (it is drifting right)
    // therefore we need to speed up right motor and slow left motor and vice versa
  
    correction = kp*error + ki*sumError + kd*rateError;   // end result of controller to be used to adjust motors
  
    // if error +ve robot is moving to the right; if error is -ve moving left
    // therefore want to speed up left motor/slow right motor if error is positive and vice versa
  
    // rightAdjustedSpeed += correction;        // adjust right side motor speed
    // leftAdjustedSpeed -= correction;         // adjust left side motor speed
  }

  else  {
    // make no motor corrections
  }

prevError = error;
prevTime = currTime;

prevRight = rightDistance;
prevLeft = leftDistance;

}
