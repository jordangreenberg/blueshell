const double tolerance_orient = 0.3;

void isOriented(){
  scooch_scooch();
  bool oriented = false;
  while (oriented == false){
  readSensors ();
  delay (30);
  readSensor5();    
    if (distance5 < (1-tolerance_orient)*distance1){ // checks if sensors are reading similar values
      if (distance4 < 10){
      rotate_counter_clockwise();
      delay (200);
      brake();
      }
      else {
      rotate_clockwise();
      delay (200);
      brake();
      }      
      if ((distance5 > (1-tolerance_orient) * distance1) && (distance5 < (1 + tolerance_orient) * distance1)){
        oriented = true;
      }
    }      
    if (distance1 < (1-tolerance_orient)*distance5){
      if (distance2 < 10){
      rotate_clockwise();
      delay (200);
      brake();
      }
      else {
      rotate_counter_clockwise();
      delay (200);
      brake();
      }
      if ((distance5 > (1-tolerance_orient) * distance1) && (distance5 < (1 + tolerance_orient) * distance1)){
      oriented = true;
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
    } 
    scooch_scooch() ;
  }   
}  




