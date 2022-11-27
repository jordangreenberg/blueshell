//# include <PID_v1.h>
//
//double Setpoint, SetpointReverse, InputDirect, OutputDirect;
//double InputReverse, OutputReverse;
//
//// Tune kp THEN kd, THEN ki as needed. May need to have seperate k values for direct/reverse controllers
//double kp_1 = 0.3;
//double ki_1 = 1.9;
//double kd_1 = 1.9;
//
//// Direct and reverse PIDs to make adjustment in each direction
//
//PID DirectPID(&InputDirect, &OutputDirect, &Setpoint, kp, ki, kd, DIRECT);
//PID ReversePID(&InputReverse, &OutputReverse, &SetpointReverse, kp, ki, kd, REVERSE);
//// & indicates variable value passed to function may change by function
//
//int rightMaxSpeed = 115;
//int rightMinSpeed = 60;
////int leftMaxSpeed = 140;
////int leftMinSpeed = 115;
//
////Wheel 4: Max 115, min 60;
////wheel 2: Max 140, min 105;
//
//double defaultRight = 120;
//double defaultLeft = 80;
//double rightSpeed = defaultRight;
//double leftSpeed = defaultLeft;

//double orientation = 3;

//// Motor 1
//int M1enA = 12;
//int M1in1 = 34;
//int M1in2 = 36;
//// Motor 2
//int M2enA = 9;
//int M2in1 = 22;
//int M2in2 = 24;
//// Motor 3
//int M3enA = 11;
//int M3in1 = 30;
//int M3in2 = 32;
//// Motor 4
//int M4enA = 10;
//int M4in1 = 26;
//int M4in2 = 28;

//void setup()
//{
//
//
//// Setpoint is desired distance from wall to right side robot
//Setpoint = 8;
//SetpointReverse = 8;
//
//// turn PID on
//DirectPID.SetMode(AUTOMATIC);
//DirectPID.SetOutputLimits(0, 75);
//
//ReversePID.SetMode(AUTOMATIC);
//ReversePID.SetOutputLimits(0, 75);
//
//  // set motor output
//  pinMode(M1enA, OUTPUT);
//  pinMode(M1in1, OUTPUT);
//  pinMode(M1in2, OUTPUT);
//  pinMode(M2enA, OUTPUT);
//  pinMode(M2in1, OUTPUT);
//  pinMode(M2in2, OUTPUT);
//  pinMode(M3enA, OUTPUT);
//  pinMode(M3in1, OUTPUT);
//  pinMode(M3in2, OUTPUT);
//  pinMode(M4enA, OUTPUT);
//  pinMode(M4in1, OUTPUT);
//  pinMode(M4in2, OUTPUT);
//   Serial.begin(9600);
//}




void drive_pid(); {

  // this function will run the motors in both directions at a fixed speed
  // turn on motor in forward direction
  orientation = newDirection;
  pid_controller();

  if (orientation == 1) {
    digitalWrite(M2in1, LOW);
    digitalWrite(M2in2, HIGH);
    // set speed to 200 out of possible range 0~255
    analogWrite(M2enA, leftSpeed); //115);

    digitalWrite(M4in1, LOW);
    digitalWrite(M4in2, HIGH);
    // set speed to 200 out of possible range 0~255
    analogWrite(M4enA, rightSpeed);

    rightMaxSpeed = 145;
    rightMinSpeed = 60;
    defaultRight = 80;
    defaultLeft = 105;

  }

  if (orientation == 2) {
    digitalWrite(M2in1, HIGH);
    digitalWrite(M2in2, LOW);
    // set speed to 200 out of possible range 0~255
    analogWrite(M2enA, rightSpeed); //115);

    digitalWrite(M4in1, HIGH);
    digitalWrite(M4in2, LOW);
    // set speed to 200 out of possible range 0~255
    analogWrite(M4enA, leftSpeed);

    rightMaxSpeed = 140;
    rightMinSpeed = 105;
    defaultRight = 120;
    defaultLeft = 80;
  }

  if (orientation == 3) {

    digitalWrite(M1in1, LOW);
    digitalWrite(M1in2, HIGH);
    // set speed to 200 out of possible range 0~255
    analogWrite(M1enA, rightSpeed);

    digitalWrite(M3in1, LOW);
    digitalWrite(M3in2, HIGH);
    // set speed to 200 out of possible range 0~255
    analogWrite(M3enA, leftSpeed);

    rightMaxSpeed = 90;
    rightMinSpeed = 50;
    defaultRight = 60;
    defaultLeft = 64;
  }

  if (orientation == 4) {
    Setpoint = 10;
    SetpointReverse = 11;

    digitalWrite(M1in1, HIGH);
    digitalWrite(M1in2, LOW);
    // set speed to 200 out of possible range 0~255
    analogWrite(M1enA, leftSpeed);

    digitalWrite(M3in1, HIGH);
    digitalWrite(M3in2, LOW);
    // set speed to 200 out of possible range 0~255
    analogWrite(M3enA, rightSpeed);

    rightMaxSpeed = 190;
    rightMinSpeed = 40;
    defaultRight = 55;
    defaultLeft = 69;
  }

}





double pid_controller() {
  // put your main code here, to run repeatedly:

  rightDistance = readSensors();


  if ( (1 <= rightDistance) && (rightDistance <= 25))
  {
    Serial.print("   Right distance = ");
    Serial.print(rightDistance);
    Serial.println();

    if (rightDistance == Setpoint)
    {
      rightSpeed = defaultRight; //80;
      leftSpeed = defaultLeft; //120;
      //Do nothing/no changes & motors remain unchanged
      Serial.print("  Right distance = ");
      Serial.print(rightDistance);
      Serial.println();
    }

    if (rightDistance < Setpoint)
    {
      InputDirect = rightDistance;
      DirectPID.Compute();
      rightSpeed = OutputDirect;
      if (rightSpeed >= 255) {
        rightSpeed = 255;
      }
      if (rightSpeed <= 60) {
        rightSpeed = 60;
      }
      rightSpeed = map(rightSpeed, 60, 255, rightMaxSpeed, rightMinSpeed);
      leftSpeed = defaultLeft;


      Serial.print("   OutputDirect = ");
      Serial.print(OutputDirect);
      Serial.print("   Right Motor Speed = ");
      Serial.print(rightSpeed);
      Serial.print("   Right distance = ");
      Serial.print(rightDistance);
      Serial.println();
    }

    if (rightDistance > Setpoint)
    {
      InputReverse = rightDistance;
      ReversePID.Compute();
      rightSpeed = OutputReverse;
      if (rightSpeed <= 60) {
        rightSpeed = 60;
      }
      if (rightSpeed >= 255) {
        rightSpeed = 255;
      }
      rightSpeed = map(rightSpeed, 60, 255, rightMinSpeed, rightMaxSpeed);
      leftSpeed = defaultLeft + 30;


      Serial.print("   OutputReverse = ");
      Serial.print(OutputReverse);
      Serial.print("   rightMotorSpeed = ");
      Serial.print(rightSpeed);
      Serial.print("   Right distance = ");
      Serial.print(rightDistance);
      Serial.println();


    }
  }
  else {
    rightSpeed = defaultRight;
    leftSpeed = defaultLeft;
    Serial.print(" distance too far = ");
    Serial.print(rightDistance);
    Serial.println();
  }
}
