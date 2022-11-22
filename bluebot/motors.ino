#define DEFAULT_SPEED 180
#define ROTATE_TIME 250

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

void drive()
{
  set_speed(*right_en, *rightSpeed);
  set_speed(*left_en, *leftSpeed);
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

// Stops all motors
void brake() {
  set_speed(motor1_en, 0);
  set_speed(motor2_en, 0);
  set_speed(motor3_en, 0);
  set_speed(motor4_en, 0);
}

// Function to rotate the robot in baby steps (ideally 2 degrees at a time)
/*void rotate()
{
  // Set motor directions to rotate clockwise
  change_direction(false, motor1_in1, motor1_in2);
  change_direction(true, motor2_in1, motor2_in2);
  change_direction(true, motor3_in1, motor3_in2);
  change_direction(false, motor4_in1, motor4_in2);

  // Set rotate speed
  set_speed(motor1_en, ROTATE_SPEED);
  set_speed(motor2_en, ROTATE_SPEED);
  set_speed(motor3_en, ROTATE_SPEED);
  set_speed(motor4_en, ROTATE_SPEED);

  delay(ROTATE_TIME);

  // Set rotate speed
  brake();
}
*/
// TODO: Check this function to make sure motor assignments/sensors match real life
// TODO: Check the ratios now that we have new motors
void change_heading(int forwardMotor)
{
  // Stop all motors
  set_speed(motor1_en, 0);
  set_speed(motor2_en, 0);
  set_speed(motor3_en, 0);
  set_speed(motor4_en, 0);
  
  if (forwardMotor == 1)
  {
    // Assign right/left motors, set direction to forward
    rightSpeed = &motor4_speed;
    leftSpeed = &motor2_speed;
    right_en = &motor4_en;
    left_en = &motor2_en;
    motor4_forward = false;
    motor2_forward = false;
    change_direction(motor4_forward, motor4_in1, motor4_in2);
    change_direction(motor2_forward, motor2_in1, motor2_in2);

    // Assign right/left distances
    rightDistance = &distance4;
    leftDistance = &distance2;
    prevRight = &prevDistance4;
    prevLeft = &prevDistance2;
    forwardDistance = &distance1;
    backDistance = &distance3;

    // Set forward motors to default speed
    *rightSpeed = DEFAULT_SPEED - 55;
    *leftSpeed = DEFAULT_SPEED;
  }
  else if (forwardMotor == 2)
  {
    // Assign right/left motors, set direction to forward
    rightSpeed = &motor1_speed;
    leftSpeed = &motor3_speed;
    right_en = &motor1_en;
    left_en = &motor3_en;
    motor1_forward = false; // BEWARE CHANGED THIS TO FALSE
    motor3_forward = false;
    change_direction(motor1_forward, motor1_in1, motor1_in2);
    change_direction(motor3_forward, motor3_in1, motor3_in2);

    // Assign right/left distances
    rightDistance = &distance1;
    leftDistance = &distance3;
    prevRight = &prevDistance1;
    prevLeft = &prevDistance3;
    forwardDistance = &distance2;
    backDistance = &distance4;

    // Set forward motors to default speed
    *rightSpeed = DEFAULT_SPEED-68;
    *leftSpeed = DEFAULT_SPEED-61;
  }
  else if (forwardMotor == 3)
  {
    // Assign right/left motors, set direction to backward
    rightSpeed = &motor2_speed;
    leftSpeed = &motor4_speed;
    right_en = &motor2_en;
    left_en = &motor4_en;
    motor2_forward = true;
    motor4_forward = true;
    change_direction(motor2_forward, motor2_in1, motor2_in2);
    change_direction(motor4_forward, motor4_in1, motor4_in2);

    // Assign right/left distances
    rightDistance = &distance2;
    leftDistance = &distance4;
    prevRight = &prevDistance2;
    prevLeft = &prevDistance4;
    forwardDistance = &distance3;
    backDistance = &distance1;

    // Set forward motors to default speed
    *rightSpeed = DEFAULT_SPEED;
    *leftSpeed = DEFAULT_SPEED - 55;
  }
  else if (forwardMotor == 4)
  {
    // Assign right/left motors, set direction to backward
    rightSpeed = &motor3_speed;
    leftSpeed = &motor1_speed;
    right_en = &motor3_en;
    left_en = &motor1_en;
    motor3_forward = true;
    motor1_forward = true;
    change_direction(motor3_forward, motor3_in1, motor3_in2);
    change_direction(motor1_forward, motor1_in1, motor1_in2);

    // Assign right/left distances
    rightDistance = &distance3;
    leftDistance = &distance1;
    prevRight = &prevDistance3;
    prevLeft = &prevDistance1;
    forwardDistance = &distance4;
    backDistance = &distance2;

    // Set forward motors to default speed
    *rightSpeed = DEFAULT_SPEED - 61;
    *leftSpeed = DEFAULT_SPEED - 68;
  }
}

int reverseHeading(int forwardMotor) {
  if (forwardMotor == 1) {
    return 3;
  }
  else if (forwardMotor == 2) {
    return 4;
  }
  else if (forwardMotor == 3) {
    return 1;
  }
  else {
    return 2;
  }
}

int rotateHeading(int rotateDirection, int forwardMotor) {
  int newHeading;
  if (rotateDirection == RIGHT) {
    newHeading = forwardMotor - 1;
  }
  else {
    newHeading = forwardMotor + 1;
  }

  // Make sure newHeading is within bounds of 1-4
  if (newHeading < 1) {
    newHeading = 4;
  }
  else if (newHeading > 4) {
    newHeading = 1;
  }

  return newHeading;
}

void constrain_speeds()
{
  if (*rightSpeed < 0)
  {
    *rightSpeed = 0;
  }
  else if (*rightSpeed > 255)
  {
    *rightSpeed = 255;
  }
  if (*leftSpeed < 0)
  {
    *leftSpeed = 0;
  }
  else if (*leftSpeed > 255)
  {
    *leftSpeed = 255;
  }
}

void adjustSpeeds(double correction)
{
//  if (drift == RIGHT)
//  {
    *rightSpeed += (int) correction;
    *leftSpeed -= (int) correction;
//  }
//  else
//  {
//    *leftSpeed += (int) correction;
//    *rightSpeed -= (int) correction;
//  }
  constrain_speeds();
}
// END OF MOTOR CONTROLLER FUNCTIONS //////////////////////////
