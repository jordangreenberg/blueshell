#define RIGHT 1
#define LEFT 2

double error;
double prevError;
double sumError;
double rateError;

double kp = 0.0005; // increase Kp decreases rise time
double ki = 0.05;
double kd = 0.20; // increase Kd decreases overshoot

unsigned long currTime;
unsigned long prevTime;
double elapsedTime;

int drift;
double correction;
double rightAdjustedSpeed;
double leftAdjustedSpeed;

/*
float prevRight;
float prevLeft;
*/

void init_controller() {
  prevError = 0;
  sumError = 0;
  currTime = millis();
  prevTime = 0;
  /*
  prevRight = rightDistance;
  prevLeft = leftDistance;
  */
}

double pid_controller(float rightDistance, float leftDistance, float prevRight, float prevLeft) {
  // Calculate elapsed time since controller last executed
  currTime = millis();
  elapsedTime = currTime - prevTime;
    
  // *** may want to adjust multiplyer for corridor checks from 1.1 to something else
  
  // TODO: confirm these conditions and drift directions, see issue on GitHub
  if (rightDistance < prevRight*1.75 && rightDistance > prevRight*0.25) {               
    // if current distance increased from prev measurement by more than 10%, new corridor detected
    // if current distance decreased from prev measurement by more than 10%, current corridor narrowed (loading zone to corridor)
    // when the current hallway changed revealing new paths, we will take the error measurement from the left side

    error = rightDistance - prevRight;                    // want right distance measurements to remain constant
    sumError += error * elapsedTime;                      // cumulative error for integral controller 
    rateError = (error - prevError) / elapsedTime;        // rate error for derivative controller

    // if the error is positive that means the robot is moving further from the right wall (it is drifting left)
    // therefore we need to speed up left motor and slow right motor and vice versa
  
    correction = 0.0001*kp*error + ki*sumError + kd*rateError;   // end result of controller to be used to adjust motors
  
    // if error +ve robot is moving to the right; if error is -ve moving left
    // therefore want to speed up left motor/slow right motor if error is positive and vice versa
  
    // rightAdjustedSpeed -= correction;        // adjust right side motor speed
    // leftAdjustedSpeed += correction;         // adjust left side motor speed
    if (rightDistance > prevRight){
      drift = LEFT;
    }
    else {
      drift = RIGHT;
    }
  }

  else if (leftDistance < prevLeft*1.75 && leftDistance > prevLeft*0.25) {       
    // in case right side has a path change, now using the left side as the error calculator
    // if current distance increased from prev measurement by more than 10%, new corridor detected
    // if current distance decreased from prev measurement by more than 10%, current corridor narrowed (loading zone to corridor)
    // when the current hallway changed revealing new paths on both sides, robot must stop to recalculate new distance measurements


    error = leftDistance - prevLeft;                      // want left distance measurements to remain constant
    sumError += error * elapsedTime;                      // cumulative error for integral controller 
    rateError = (error - prevError) / elapsedTime;        // rate error for derivative controller

    // if the error is positive that means the robot is moving further from the left wall (it is drifting right)
    // therefore we need to speed up right motor and slow left motor and vice versa
  
    correction = 0.0001*(kp*error + ki*sumError + kd*rateError);   // end result of controller to be used to adjust motors
  
    // if error +ve robot is moving to the right; if error is -ve moving left
    // therefore want to speed up left motor/slow right motor if error is positive and vice versa
  
    // rightAdjustedSpeed += correction;        // adjust right side motor speed
    // leftAdjustedSpeed -= correction;         // adjust left side motor speed
    if (leftDistance > prevLeft){
      drift = RIGHT;
    }
    else {
      drift = LEFT;
    }
  }

  else  {
    // make no motor corrections
    correction = 0;
  }

  prevError = error;
  prevTime = currTime;
  
  prevRight = rightDistance;
  prevLeft = leftDistance;

  return correction;

}
