const double BOBERT_DIAMETER = 22.86;
const double ONE_FOOT = 30.48;
const double tolerance_orient = 0.2;
bool isOriented (float sensor5_reading, float sensor1_reading){
  bool oriented = false;
  while (oriented == false){
    if (sensor5_reading < (1-tolerance_orient)*sensor1_reading){ // checks if sensors are reading similar values, if not, rotate until they are within the tolerance
      rotate_clockwise();
      delay (250);
      brake ();
      if sensor5_reading >(1-tolerance_orient) * sensor1_reading && sensor5_reading < (1 + tolerance_orient) * sensor1_reading{
        oriented = true;
      }
    } // end of if sensor5 < (1-tolerance)*sensor1
    else if (sensor1_reading < (1-tolerance_orient)*sensor5_reading){
      rotate_counter_clockwise();
      delay(250);
      brake ();
      if (sensor1_reading >(1-tolerance_orient) * sensor5_reading && sensor1_reading < (1 + tolerance_orient) * sensor5_reading) {
        oriented = true;
      }
    } // end of if sensor1 < (1-tolerance)*sensor5
    else{
      oriented = true;
    }
  } // end of while loop
  return oriented;
} // end of isOriented()
