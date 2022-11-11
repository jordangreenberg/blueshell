#define DEFAULT_SPEED 150
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

// TODO: Check this function to make sure motor assignments/sensors match real life
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
  }
  else if (forwardMotor == 2)
  {
    // Assign right/left motors, set direction to forward
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
  }
  else if (forwardMotor == 3)
  {
    // Assign right/left motors, set direction to backward
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
  }
  else if (forwardMotor == 4)
  {
    // Assign right/left motors, set direction to backward
    rightSpeed = &motor1_speed;
    leftSpeed = &motor3_speed;
    right_en = &motor1_en;
    left_en = &motor3_en;
    motor1_forward = false;
    motor3_forward = false;
    change_direction(motor1_forward, motor1_in1, motor1_in2);
    change_direction(motor3_forward, motor3_in1, motor3_in2);

    // Assign right/left distances
    rightDistance = &distance1;
    leftDistance = &distance3;
  }

  // Set forward motors to default speed
  *rightSpeed = DEFAULT_SPEED;
  *leftSpeed = DEFAULT_SPEED;
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
  if (drift == RIGHT)
  {
    *rightSpeed += (int) correction;
    *leftSpeed -= (int) correction;
  }
  else
  {
    *leftSpeed += (int) correction;
    *rightSpeed -= (int) correction;
  }
  constrain_speeds();
}

void drive()
{
  set_speed(*right_en, *rightSpeed);
  set_speed(*left_en, *leftSpeed);
}
// END OF MOTOR CONTROLLER FUNCTIONS //////////////////////////
