// connect motor controller pins to Arduino digital pins 
#define M1_ENCODER_A 18 
#define M1_ENCODER_B 47
#define M2_ENCODER_A 19
#define M2_ENCODER_B 49
#define M3_ENCODER_A 20
#define M3_ENCODER_B 51
#define M4_ENCODER_A 21
#define M4_ENCODER_B 53

volatile unsigned long M1_Count = 0;
volatile unsigned long M2_Count = 0;
volatile unsigned long M3_Count = 0;
volatile unsigned long M4_Count = 0;

// Motor 1

int M1enA = 12; 
int M1in1 = 34; 
int M1in2 = 36; 



// Motor 2
int M2enA = 9; 
int M2in1 = 22; 
int M2in2 = 24; 



// Motor 3
int M3enA = 11; 
int M3in1 = 30; 
int M3in2 = 32; 



// Motor 4
int M4enA = 10; 
int M4in1 = 26; 
int M4in2 = 28; 

double correction;
 
void setup() 
{ 
  // set motor output
  pinMode(M1enA, OUTPUT); 
  pinMode(M1in1, OUTPUT); 
  pinMode(M1in2, OUTPUT); 
  pinMode(M2enA, OUTPUT); 
  pinMode(M2in1, OUTPUT); 
  pinMode(M2in2, OUTPUT); 
  pinMode(M3enA, OUTPUT); 
  pinMode(M3in1, OUTPUT); 
  pinMode(M3in2, OUTPUT); 
  pinMode(M4enA, OUTPUT); 
  pinMode(M4in1, OUTPUT); 
  pinMode(M4in2, OUTPUT); 
  
  // set all the motor control pins to outputs 
  pinMode(M1_ENCODER_A, INPUT);
  pinMode(M1_ENCODER_B, INPUT);
  pinMode(M2_ENCODER_A, INPUT);
  pinMode(M2_ENCODER_B, INPUT);
  pinMode(M3_ENCODER_A, INPUT);
  pinMode(M3_ENCODER_B, INPUT);
  pinMode(M4_ENCODER_A, INPUT);
  pinMode(M4_ENCODER_B, INPUT);
  
  // initialize hardware interrupts
  attachInterrupt(digitalPinToInterrupt(18), M1_EncoderEvent, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), M2_EncoderEvent, CHANGE);
  attachInterrupt(digitalPinToInterrupt(20), M3_EncoderEvent, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), M4_EncoderEvent, CHANGE);
  
  Serial.begin(9600);
} 


void loop() 
{ 
  // this function will run the motors in both directions at a fixed speed 
  // turn on motor in forward direction 

  
//  digitalWrite(M1in1, LOW); 
//  digitalWrite(M1in2, HIGH); 
//  // set speed to 200 out of possible range 0~255 
//  analogWrite(M1enA, 115); 

  digitalWrite(M2in1, LOW); 
  digitalWrite(M2in2, HIGH); 
  // set speed to 200 out of possible range 0~255 
  analogWrite(M2enA, 130); 

//  digitalWrite(M3in1, LOW); 
//  digitalWrite(M3in2, HIGH); 
//  // set speed to 200 out of possible range 0~255 
//  analogWrite(M3enA, 130); 

  digitalWrite(M4in1, LOW); 
  digitalWrite(M4in2, HIGH); 
  // set speed to 200 out of possible range 0~255 
  analogWrite(M4enA, 124); 
  
  delay(2000); 
 
  Serial.print("M1 Count: ");
  Serial.println(M1_Count);
  Serial.print("M2 Count: ");
  Serial.println(M2_Count);
  Serial.print("M3 Count: ");
  Serial.println(M3_Count);
  Serial.print("M4 Count: ");
  Serial.println(M4_Count);
  Serial.println();
  delay(500);
} 


void M1_EncoderEvent() {                             
  if (digitalRead(M1_ENCODER_A) == HIGH) {
    if (digitalRead(M1_ENCODER_B) == LOW) {
      M1_Count++;
    } else {
      M1_Count--;
    }
  } else {
    if (digitalRead(M1_ENCODER_B) == LOW) {
      M1_Count--;
    } else {
      M1_Count++;
    }
  }
}

// encoder event for the interrupt call
void M2_EncoderEvent() {
  if (digitalRead(M2_ENCODER_A) == HIGH) {
    if (digitalRead(M2_ENCODER_B) == LOW) {
      M2_Count++;
    } else {
      M2_Count--;
    }
  } else {
    if (digitalRead(M2_ENCODER_B) == LOW) {
      M2_Count--;
    } else {
      M2_Count++;
    }
  }
}

// encoder event for the interrupt call
void M3_EncoderEvent() {
  if (digitalRead(M3_ENCODER_A) == HIGH) {
    if (digitalRead(M3_ENCODER_B) == LOW) {
      M3_Count++;
    } else {
      M3_Count--;
    }
  } else {
    if (digitalRead(M3_ENCODER_B) == LOW) {
      M3_Count--;
    } else {
      M3_Count++;
    }
  }
}

// encoder event for the interrupt call
void M4_EncoderEvent() {
  if (digitalRead(M4_ENCODER_A) == HIGH) {
    if (digitalRead(M4_ENCODER_B) == LOW) {
      M4_Count++;
    } else {
      M4_Count--;
    }
  } else {
    if (digitalRead(M1_ENCODER_B) == LOW) {
      M4_Count--;
    } else {
      M4_Count++;
    }
  }
}
 
// encoder event for the interrupt call
/*void rightEncoderEvent() {
  if (digitalRead(RH_ENCODER_A) == HIGH) {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount++;
    } else {
      rightCount--;
    }
  } else {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount--;
    } else {
      rightCount++;
    }
  }
}
*/
