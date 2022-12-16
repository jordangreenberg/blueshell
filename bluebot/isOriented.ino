const double tolerance_orient = 0.15;

void isOriented(){
  //Serial.println("In orienting, before scooching");
  scooch_scooch();
  bool oriented = false;
  int i = 0;
  while (oriented == false){
    readSensors();
    delay (30);
    //Serial.print("Orienting iteration: ");
    //Serial.print(i);
    //Serial.print(" | Oriented = ");
    //Serial.println(oriented);
      if (d5avg < (1-tolerance_orient)*d1avg){ // checks if sensors are reading similar values
        if (d4avg < 10){
          rotate_counter_clockwise();
          delay (200);
          brake();
        }
        else {
          rotate_clockwise();
          delay (200);
          brake();
        }
        readSensors();      
        if ((d5avg > (1-tolerance_orient) * d1avg) && (d5avg < (1 + tolerance_orient) * d1avg)){
          oriented = true;
          break;
        }
      }      
      if (d1avg < (1-tolerance_orient)*d5avg){
        if (d2avg < 10){
          rotate_clockwise();
          delay (200);
          brake();
        }
        else {
          rotate_counter_clockwise();
          delay (200);
          brake();
        }
        readSensors();
        if ((d5avg > (1-tolerance_orient) * d1avg) && (d5avg < (1 + tolerance_orient) * d1avg)){
          oriented = true;
          break;
        }
      }      
      else{
        oriented = true; 
      }
     /* Serial.println("d5:");
      Serial.print(distance5);
      Serial.println(" ");
      Serial.print("d1");
      Serial.println(" ");
      Serial.println(distance1);
      Serial.println(" ");
      Serial.println("orrient?:");
      Serial.print(oriented);
      Serial.println(" ");*/
 
      scooch_scooch();
      i++;
   } 
//   Serial.println("WE ARE ORIENTED");  
}  
