const double BOBERT_DIAMETER = 22.86; // Bobert's diameter in cm
const double ONE_FOOT = 30.48; // One foot in cm
const double ORIENT_CLEARANCE = 3.0; // Orienting clearance in cm
const double FORWARD_SAFE = 2.0; // Safe distance to move forward in cm
const double SAFE_DISTANCE = 3.5; // Safe distance for all four directions in cm
const double CLEARANCE_TOLERANCE = 5.0; // Tolerance for clearance in cm

bool isOriented(float rightDistance, float leftDistance, float forwardDistance, float backDistance)
{
  // Right Distance + Left Distance + Diameter should be one foot, two feet, or four feet
  // The same is true for front and back sensors
  // If it's not, then we consider bobert to be disoriented
  int right = (int) (rightDistance * 100);
  int left = (int) (leftDistance * 100);
  int front = (int) (forwardDistance * 100 - 150); // subtract 1.5cm because front/back diameter
  int back = (int) (backDistance * 100);
  int diameter = (int) (BOBERT_DIAMETER * 100);
  int foot = (int) (ONE_FOOT * 100);
  int two_feet = foot * 2;
  int four_feet = foot * 4;
  int totalWidthSpan = right + left + diameter;
  int totalLengthSpan = front + back + diameter;
  int orientClearance = (int) (ORIENT_CLEARANCE * 100);
  
  int upperClearance  = foot - orientClearance;
  int widthRemainder = totalWidthSpan % foot;
  int lengthRemainder = totalLengthSpan % foot;

  // If the robot is oriented to one foot +/- orient clearance
  if ((totalWidthSpan <= foot + orientClearance && totalWidthSpan >= foot - orientClearance) && (totalLengthSpan <= foot + orientClearance && totalLengthSpan >= foot - orientClearance)) {
    return true;
  }
  else if ((totalWidthSpan <= two_feet + orientClearance && totalWidthSpan >= two_feet - orientClearance) && (totalLengthSpan <= two_feet + orientClearance && totalLengthSpan >= two_feet - orientClearance)) {
    return true;
  }
  else if ((totalWidthSpan <= four_feet + orientClearance && totalWidthSpan >= four_feet - orientClearance) && (totalLengthSpan <= four_feet + orientClearance && totalLengthSpan >= four_feet - orientClearance)) {
    return true;
  }
  else {
    rotate(); // Rotate 2 degrees
    return false;
  }
}

bool isForwardSafe(float forwardDistance) {
  if (forwardDistance > FORWARD_SAFE) {
    return true;
  }
  else {
    return false;
  }
}

bool isFourDirectionsClear(float forwardDistance, float rightDistance, float leftDistance, float backDistance) {
  if (forwardDistance > SAFE_DISTANCE && rightDistance > SAFE_DISTANCE && leftDistance > SAFE_DISTANCE && backDistance > SAFE_DISTANCE) {
    return true;
  }
  else {
    return false;
  }
}

// Determine if there is a corridor on the left or right sice
// Return 0 if no corridor
// Return 1 if corridor on the right
// Return 2 if corrdior on the left
int findCorridor(float prevLeft, float leftDistance, float prevRight, float rightDistance, float backDistance, float frontDistance) {
  if (rightDistance > prevRight + ONE_FOOT) {
    corridorBackDistance = backDistance;
    corridorFrontDistance = frontDistance;
    return 1;
  }
  else if (leftDistance > prevLeft + ONE_FOOT) {
    corridorBackDistance = backDistance;
    corridorFrontDistance = frontDistance;
    return 2;
  }
  else {
    return 0;
  }
}

bool clearance(float backDistance, float corridorBackDistance, float frontDistance, float corridorFrontDistance) {
  if (backDistance > (corridorBackDistance + BOBERT_DIAMETER / 2) && frontDistance < (corridorFrontDistance - (BOBERT_DIAMETER / 2 + CLEARANCE_TOLERANCE))) {
    return true;
  }
  else {
    false;
  }
}


/*
//function [pos] = move_forward(prev_pos, speed, s_cmd, s_rply)
//   moving in our heading direction lol yay so fun 
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:



pos = prev_pos;

  if pos(3) == 0 {
      cmdstring = [strcat('d1-0.5',num2str(speed)) newline];             % Build command string to move bot
      reply = tcpclient_write(cmdstring, s_cmd, s_rply);
      pos(1) = prev_pos(1) + 0.5

          
  else if pos(3) == 90 {
      cmdstring = [strcat('w1-0.5',num2str(speed)) newline];             % Build command string to move bot
      reply = tcpclient_write(cmdstring, s_cmd, s_rply);
      pos(2) = prev_pos(2) + 0.5 }

  else if pos(3) == 180 {
      cmdstring = [strcat('a1-0.5',num2str(speed)) newline];             % Build command string to move bot
      reply = tcpclient_write(cmdstring, s_cmd, s_rply);
      pos(1) = prev_pos(1) - 0.5 }

      
  else if pos(3) == 270 {
      cmdstring = [strcat('s1-0.5',num2str(speed)) newline];             % Build command string to move bot
      reply = tcpclient_write(cmdstring, s_cmd, s_rply);
      pos(2) = prev_pos(2) - 0.5 }

  }

}

// function [pos, step_out, state] = check_peripherals(u, u_prev, pos, step, state, speed, s_cmd, s_rply)
// UNTITLED2 Summary of this function goes here
//   this function will check the peripherals of the robot. need to consider
//  which direction the robot is moving, ie the heading and then check.
//   this will prevent us from getting stuck
// call the clearance function in this function

int step_out = step;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600)

}

void loop() {
  // put your main code here, to run repeatedly:


  if step >= 15 {
      if (pos(3) == 0) || (pos(3) == 180) {
          // need to check u2 and u4
          if (pos(3) == 0) && (u(1) > 12) {
              // if the way we are going is clear
              pos(3) = pos(3); 
          else if (pos(3) == 180) && (u(3) > 12) {
              pos(3) = pos(3);}
          else if u(2) > 3*(u(1)) || u(2) > 3*(u(3)){
              //going up takes priotity over going down if in a big open corridor
              state = 1; }
              if state == 1 {
                  [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
              }
              pos(3) = 90;
              step_out = 0;
          else if u(4) > 3*(u(1)) || u(4) > 3*(u(3)) {
              state = 1; }
              if state == 1 {
                  [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
              }
              pos(3) = 270;
              step_out = 0;
          else {
              pos(3) = pos(3);
            }
          }
        }
      
      
      if (pos(3) == 90) || (pos(3) == 270) {
          if (pos(3) == 90) && (u(2) > 12) {
              //if the way we are going is clear
              pos(3) = pos(3);
          else if (pos(3) == 270) && (u(4) > 12) {
              pos(3) = pos(3); }
              //need to check u3 and u1
          else if u(3) > 3*(u(2)) || u(3) > 3*(u(4)) {
              state = 1; }
              if state == 1 {
                  [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
              }
              pos(3) = 180;
              step_out = 0;
            
          else if u(1) > 3*(u(2)) || u(1) > 3*(u(4)) {
              state = 1; }
              if state == 1 {
                  [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
              }
              pos(3) = 0;
              step_out = 0;
              
          else {
              pos(3) = pos(3);
          }
        }
      }
      
  }

}
*/
