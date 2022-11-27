int rightMaxSpeed;// = 115; 
int rightMinSpeed;// = 60;

double defaultRight;// = 120;
double defaultLeft;// = 80;

double orientation;// = 3;

void drive_pid() 
{ 
  // this function will run the motors in both directions at a fixed speed 
  // turn on motor in forward direction 
  pid_controller();
  
  if (forwardMotor == 1){
    digitalWrite(motor2_in1, LOW); 
    digitalWrite(motor2_in2, HIGH); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor2_en, *leftSpeed); //115);
  
    digitalWrite(motor4_in1, LOW); 
    digitalWrite(motor4_in2, HIGH); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor4_en, *rightSpeed); 
  
    rightMaxSpeed = 145;
    rightMinSpeed = 60;
    defaultRight = 80;
    defaultLeft = 105;
  
  }
  
  if (forwardMotor == 2){
    digitalWrite(motor2_in1, HIGH); 
    digitalWrite(motor2_in2, LOW); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor2_en, *rightSpeed); //115);
    
    digitalWrite(motor4_in1, HIGH); 
    digitalWrite(motor4_in2, LOW); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor4_en, *leftSpeed); 
    
    rightMaxSpeed = 140;
    rightMinSpeed = 105;
    defaultRight = 120;
    defaultLeft = 80;
  }
  
  if (forwardMotor == 3){
  
    digitalWrite(motor1_in1, LOW); 
    digitalWrite(motor1_in2, HIGH); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor1_en, *rightSpeed); 
  
    digitalWrite(motor3_in1, LOW); 
    digitalWrite(motor3_in2, HIGH); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor3_en, *leftSpeed); 
    
    rightMaxSpeed = 90;
    rightMinSpeed = 50;
    defaultRight = 60;
    defaultLeft = 64;
  }
  
  if (forwardMotor == 4){
    Setpoint = 10;
    SetpointReverse = 11;
  
    digitalWrite(motor1_in1, HIGH); 
    digitalWrite(motor1_in2, LOW); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor1_en, *leftSpeed); 
  
    digitalWrite(motor3_in1, HIGH); 
    digitalWrite(motor3_in2, LOW); 
    // set speed to 200 out of possible range 0~255 
    analogWrite(motor3_en, *rightSpeed); 
    
    rightMaxSpeed = 190;
    rightMinSpeed = 40;
    defaultRight = 55;
    defaultLeft = 69;
  }
}

double pid_controller() {
  // put your main code here, to run repeatedly:

  readSensors();
  
  
  if ( (1 <= *rightDistance) && (*rightDistance <= 25))
  {
      /*
      Serial.print("   Right distance = ");
      Serial.print(*rightDistance);
      Serial.println();
      */
      
    if (*rightDistance == Setpoint)
      {
      *rightSpeed = defaultRight; //80;
      *leftSpeed = defaultLeft; //120;
      //Do nothing/no changes & motors remain unchanged
      /*
      Serial.print("  Right distance = ");
      Serial.print(rightDistance);
      Serial.println();
      */
      }
    
    if (*rightDistance < Setpoint)
      {
      InputDirect = *rightDistance;
      DirectPID.Compute();
      *rightSpeed = OutputDirect; 
        if (*rightSpeed >= 255){
          *rightSpeed = 255;
        }
        if (*rightSpeed <= 60){
          *rightSpeed = 60;
        }
        *rightSpeed = map(*rightSpeed, 60, 255, rightMaxSpeed, rightMinSpeed);
        *leftSpeed = defaultLeft;
     
      /*  
      Serial.print("   OutputDirect = ");
      Serial.print(OutputDirect);
      Serial.print("   Right Motor Speed = ");
      Serial.print(rightSpeed);
      Serial.print("   Right distance = ");
      Serial.print(rightDistance);
      Serial.println();
      */
      }
    
    if (*rightDistance > Setpoint)
      {
      InputReverse = *rightDistance;
      ReversePID.Compute();
      *rightSpeed = OutputReverse; 
      if (*rightSpeed <= 60){
        *rightSpeed = 60;
      }
      if (*rightSpeed >= 255){
        *rightSpeed = 255;
      }
      *rightSpeed = map(*rightSpeed, 60, 255, rightMinSpeed, rightMaxSpeed);
      *leftSpeed = defaultLeft+30;
      
      /*
      Serial.print("   OutputReverse = ");
      Serial.print(OutputReverse);
      Serial.print("   rightMotorSpeed = ");
      Serial.print(rightSpeed);
      Serial.print("   Right distance = ");
      Serial.print(rightDistance);
      Serial.println();
      */
  
      
      }
    }
  else {
      *rightSpeed = defaultRight;
      *leftSpeed = defaultLeft;
      /*
      Serial.print(" distance too far = ");
      Serial.print(rightDistance);
      Serial.println();
      */
    }
}
