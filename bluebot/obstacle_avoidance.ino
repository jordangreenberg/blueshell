const double BOBERT_DIAMETER = 22.86; // Bobert's diameter in cm
const double ONE_FOOT = 30.48; // One foot in cm
const double ORIENT_CLEARANCE = 3.0; // Orienting clearance in cm
const double FORWARD_SAFE = 5; // Safe distance to move forward in cm
const double SAFE_DISTANCE = 5; // Safe distance for all four directions in cm
const double CLEARANCE_TOLERANCE = 5; // Tolerance for clearance in cm
const int SCOOCH_DELAY = 100; // How long we scooch, in milliseconds

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
 if ((d1avg >= d2avg) && (d1avg >= distance3) && (d1avg >= d4avg)){
   return 1;
 }
 if ((d2avg >= d1avg) && (d2avg >= d3avg) && (d2avg >= d4avg)){
   return 2;
 }
 if ((d3avg >= d1avg) && (d3avg >= d2avg) && (d3avg >= d4avg)){
   return 3;
 }
 if ((d4avg >= d1avg) && (d4avg >= d2avg) && (d4avg >= d3avg)){
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
  if (d1avg < SAFE_DISTANCE) {
    //Serial.println(d1avg);
    change_heading(3);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
  if (d2avg < SAFE_DISTANCE) {
    //Serial.println(d2avg);
    change_heading(4);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
  if (d3avg < (SAFE_DISTANCE+1)) {
    //Serial.println(d3avg);
    change_heading(1);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
  if (d4avg < SAFE_DISTANCE) {
    //Serial.println(d4avg);
    change_heading(2);
    drive();
    delay(SCOOCH_DELAY);
    brake();
  }
}
