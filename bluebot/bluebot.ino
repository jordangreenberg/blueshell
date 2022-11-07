char val = 0; //holds ascii from serial line

signed char i = 0; // motor 1 speed - probably rename this
signed char j = 0; // motor 2 speed - probably rename this

// MOTOR CONTROLLER FUNCTIONS /////////////////////////////////
// Code adapted from MC_PWM_clean.ino provided on Quercus
// Potentially for Uno and not Mega, will have to test
//Speeds are between -32 and 32
void set_speedA(signed char speed) 
{
  if((speed > -128) && (speed < 128))
  {
     analogWrite(9, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     analogWrite(10, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     TCCR1A |= B00110000;  //invert PWM output - using timer interrupts, will have to look more into this
  }
}
void set_speedB(signed char speed)
{
  if((speed > -128) && (speed < 128))
  {
     analogWrite(5, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     analogWrite(6, 128 + speed); // NEED TO ADAPT FOR PIN ASSIGNMENT
     TCCR0A |= B00110000;  //invert PWM output - using timer interrupts, will have to look more into this
  }
}
// END OF MOTOR CONTROLLER FUNCTIONS //////////////////////////

// Notes

// When implementing this for four wheels, I think we focus on activating two wheels at a time
// The other two wheels can be "passive" and drag along
// This should allow us to "spidercrawl" (obviously we will have to test)

// This code will also have to be adapted to use L298N drivers (I don't think it does)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Greetings bluebots");
  set_speedA(i);
  set_speedB(j);

} // end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  // This code will control two motors that are setup in left/right configuration
  // 'w' (forward), 'a' (left), 's' (backward), 'd' (right), 'k' (stop) can be input to control the motors

  if (Serial.available())
  {
    val = Serial.read();
    Serial.println(val); // print out input
    if (val == 'w')
      {
        i = i + 8;
        j = j + 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 's')
      {
        i = i - 8;
        j = j - 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 'd')
      {
        i = i + 8;
        j = j - 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 'a')
      {
        i = i - 8;
        j = j + 8;
        set_speedA(i);
        set_speedB(j);
      }
      else if(val == 'k')
      {
        i = 0;
        j = 0;
        set_speedA(i);
        set_speedB(j);
      }
  } // end of if (Serial.available())
} // end of loop()
