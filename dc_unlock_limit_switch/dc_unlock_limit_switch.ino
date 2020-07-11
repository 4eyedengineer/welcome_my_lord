//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/

#define ENABLE 8
#define DIRA 6
#define DIRB 7

int i;
boolean isLocked = false;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  rotateLock(isLocked); // initilize lock to locked state
}

void loop() {
  // TODO: replace with trigger from rasp pi
  if (digitalRead(2)){
    Serial.println("triggered");
    delay(200);
    rotateLock(isLocked);
    delay(5000); // TODO increase
    rotateLock(isLocked);
    delay(1000);
  }
}

void rotateLock(boolean isLocking){
  while(digitalRead(2) == LOW && digitalRead(3) == LOW){
    Serial.println("spinning");
    if(isLocking){
      spinClockwise();
    } else {
      spinCounterClockwise();
    }
    turnMotorOn();
  }
  isLocked = !isLocking;
  Serial.print("lock state: ");
  if(isLocked) {
    Serial.println("locked");
  } else {
    Serial.println("unlocked");
  }
  turnMotorOff();
  delay(300);
  backOffSwitch();
}

void backOffSwitch(){
  turnMotorOn();
  if(isLocked){
    spinClockwise();
  } else {
    spinCounterClockwise();
  }
  delay(750);
  turnMotorOff();
}

void spinClockwise(){
  digitalWrite(DIRB,HIGH);
  digitalWrite(DIRA,LOW);
}

void spinCounterClockwise(){
  digitalWrite(DIRA,HIGH); 
  digitalWrite(DIRB,LOW);
}

void turnMotorOn(){
  digitalWrite(ENABLE,HIGH); // enable on
}

void turnMotorOff(){
  digitalWrite(ENABLE,LOW); // enable off
}



   
