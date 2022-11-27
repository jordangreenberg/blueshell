const double BOBERT_DIAMETER = 22.86; // Bobert's diameter in cm
const double ONE_FOOT = 30.48; // One foot in cm
const double ORIENT_CLEARANCE = 3.0; // Orienting clearance in cm
const double FORWARD_SAFE = 5; // Safe distance to move forward in cm
const double SAFE_DISTANCE = 5; // Safe distance for all four directions in cm
const double CLEARANCE_TOLERANCE = 5; // Tolerance for clearance in cm
const int SCOOCH_DELAY = 250; // How long we scooch, in milliseconds

const double corriDist = 15;

bool isForwardSafe(float forwardDistance) {
  if (forwardDistance > FORWARD_SAFE) {
    return true;
  }
  else {
    return false;
  }
}

int clearestDirection() {
 readSensors();
 if ((distance1 >= distance2) && (distance1 >= distance3) && (distance1 >= distance4)){
   return 1;
 }
 if ((distance2 >= distance1) && (distance2 >= distance3) && (distance2 >= distance4)){
   return 2;
 }
 if ((distance3 >= distance1) && (distance3 >= distance2) && (distance3 >= distance4)){
   return 3;
 }
 if ((distance4 >= distance1) && (distance4 >= distance2) && (distance4 >= distance3)){
   return 4;
 }
}

// Determine if there is a corridor on the left or right sice
// Return 0 if no corridor
// Return 1 if corridor on the right
// Return 2 if corrdior on the left

int new_corridor (float prevLeft, float leftDistance, float prevRight, float rightDistance, float backDistance, float frontDistance){
  if ((rightDistance - prevRight) > 20){
    return 1;
  }
  if ((leftDistance - prevLeft) > 20){
    return 2;
  }
  else{
    return 0;
  }
}
int findCorridor(float prevLeft, float leftDistance, float prevRight, float rightDistance, float backDistance, float frontDistance) {
  if (rightDistance > prevRight + corriDist) {
    corridorBackDistance = backDistance;
    corridorFrontDistance = frontDistance;
    return 1;
  }
  else if (leftDistance > prevLeft + corriDist) {
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

void scooch_scooch() {
  readSensors();
  if (distance1 < SAFE_DISTANCE) {
    change_heading(3);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
  if (distance2 < SAFE_DISTANCE) {
    change_heading(4);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
  if (distance3 < (SAFE_DISTANCE+1)) {
    change_heading(1);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
  if (distance4 < SAFE_DISTANCE) {
    change_heading(2);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
}
