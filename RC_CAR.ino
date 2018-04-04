/*  REMOTE CONTROLLED  BLUETOOTH CAR
 *  CONTROLLED VIA AN APP TO THE ARDUINO, THE APP WAS CREATED USING MIT APP INVENTOR
 *  BY TAHER NURBHAI
 *  
 *  IMPORTANT
 *  When uploding code to the car remove Tx a Rx pins from arduino,
 *  after code has been uploaded then out pins back in.
 */
  
// we define motors pins.
int leftMotorEnable = 10; //ENA
int leftMotorForward = 6; //IN1
int leftMotorBackward = 7; //IN2

int rightMotorEnable = 11; //ENB
int rightMotorForward = 9; //IN4
int rightMotorBackward = 8; //IN3

// initialise functions
void stopMoving();
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void spin();

//used for testing
int test = 1; 

//define the ultrasonic sensor pins.
int echoPin = 12;
int triggerPin = 13;

// the speed of sound in air.
const float speedOfSound = 331.2;

//bluetooth setting
int state;
int flag = 0;
int stateStop = 0;

void setup() {
  Serial.begin(9600);  // Debugging only

  pinMode(leftMotorEnable, OUTPUT);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);

  pinMode(rightMotorEnable, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  
 }


void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }

    // activate the ultrasonic sensor
    digitalWrite(triggerPin, LOW);
    delay(2);
    digitalWrite(triggerPin, HIGH);
    delay(10);  
    digitalWrite(triggerPin, LOW);

    // Retrive the time take for the pulse to come back to the sensor
    float echoTime = pulseIn(echoPin, HIGH) / 1000000.000;
    // Calculate the distance between the sensor and an obstacle in cm
    float distanceToImpact = echoTime * speedOfSound * 100 / 2;
   // Serial.print("Distance:"); Serial.println(distanceToImpact);
   
    if (distanceToImpact >= 10){ 
    
    // if the state is 'F' the DC motor will go forward
    if (state == 'F') {
          moveForward();
        if(flag == 0){
          Serial.println("Moving Forwards");
          flag=1;
        }
    }
    
    // if the state is 'R' the motor will turn Right
    else if (state == 'R') {
          turnRight();
        if(flag == 0){
          Serial.println("Turning Right");
          flag=1;
        }
        delay(1500);
        state=3;
        stateStop=1;
    }
    
    // if the state is 'S' the motor will Stop
    else if (state == 'S' || stateStop == 1) {
          stopMoving();
        if(flag == 0){
          Serial.println("Stopping");
          flag=1;
        }
        stateStop=0;
    }
    // if the state is 'L' the motor will turn left
    else if (state == 'L') {
          turnLeft();
        if(flag == 0){
          Serial.println("Turning Left");
          flag=1;
        }
        delay(1500);
        state=3;
        stateStop=1;
    }
    // if the state is 'B' the motor will Reverse
    else if (state == 'B') {
            moveBackward();
        if(flag == 0){
          Serial.println("Reversing");
          flag=1;
        }
    }

    }
    else if (distanceToImpact < 10){
      stopMoving();
      moveBackward();
    }
    
    //For debugging purpose
    //Serial.print("state:");   Serial.println(state);
    //Serial.print("flag:");   Serial.println(flag);    
    //Serial.print("state stop:");   Serial.println(stateStop);  
}

//Function for stoping the car
void stopMoving() {
  digitalWrite(leftMotorEnable, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);

  digitalWrite(rightMotorEnable, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

//Function for moving the car forward
void moveForward() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);

}

//Function for moving the car backward
void moveBackward() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  
  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}

//Function for turning the car left
void turnLeft() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);

}

//Function for turning the car right
void turnRight() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

//Function for spinning the car
void spin(){
  
  analogWrite(leftMotorEnable, 100);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 100);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}
