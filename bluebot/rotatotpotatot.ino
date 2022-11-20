#define ROTATE_SPEED 90

int * frontSpeed;
int * backSpeed;

void rotate_clockwise (){
  rightSpeed = &motor1_speed;
  leftSpeed = &motor3_speed;
  frontSpeed = &motor2_speed;
  backSpeed = &motor4_speed;
  right_en = &motor1_en;
  left_en = &motor3_en;
  front_en = &motor2_en;
  back_en = &motor4_en;
  motor1_forward = true; // BEWARE CHANGED THIS TO FALSE
  motor3_forward = false; // idk yet need to verify
  motor2_forward = false;
  motor4_forward = true;
  change_direction(motor4_forward, motor4_in1, motor4_in2);
  change_direction(motor2_forward, motor2_in1, motor2_in2);
  change_direction(motor1_forward, motor1_in1, motor1_in2);
  change_direction(motor3_forward, motor3_in1, motor3_in2);
  *rightSpeed = ROTATE_SPEED;
  *leftSpeed = ROTATE_SPEED;
  *frontSpeed = ROTATE_SPEED;
  *backSpeed = ROTATE_SPEED;
  set_speed(*right_en, *rightSpeed);
  set_speed(*left_en, *leftSpeed);
  set_speed(*front_en, *frontSpeed);
  set_speed(*back_en, *backSpeed);
}

void rotate_counter_clockwise (){
  rightSpeed = &motor1_speed;
  leftSpeed = &motor3_speed;
  frontSpeed = &motor2_speed;
  backSpeed = &motor4_speed;
  right_en = &motor1_en;
  left_en = &motor3_en;
  front_en = &motor2_en;
  back_en = &motor4_en;
  motor1_forward = false; // BEWARE CHANGED THIS TO FALSE
  motor3_forward = true; // idk yet need to verify
  motor2_forward = true;
  motor4_forward = false;
  change_direction(motor4_forward, motor4_in1, motor4_in2);
  change_direction(motor2_forward, motor2_in1, motor2_in2);
  change_direction(motor1_forward, motor1_in1, motor1_in2);
  change_direction(motor3_forward, motor3_in1, motor3_in2);
  *rightSpeed = ROTATE_SPEED;
  *leftSpeed = ROTATE_SPEED;
  *frontSpeed = ROTATE_SPEED;
  *backSpeed = ROTATE_SPEED;
  set_speed(*right_en, *rightSpeed);
  set_speed(*left_en, *leftSpeed);
  set_speed(*front_en, *frontSpeed);
  set_speed(*back_en, *backSpeed);

}
