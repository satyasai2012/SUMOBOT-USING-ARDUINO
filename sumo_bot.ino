//Sumobot_v2_test-1

// Motor control pins
const int motorIn1Pin = 10;   // Pin connected to in1 of L293D for left motor control
const int motorIn2Pin = 11;   // R MOTOR

const int motorIn3Pin = 5;    // 
const int motorIn4Pin = 6;    // L MOTOR

/*const int motor2_LEN = 7;    // 
const int motor2_REN = 8;
const int motor1_LEN = 13;    // Pin connected to in1 of L293D for motor control
const int motor1_REN = 12; */   // Pin connected to in2 of L293D for motor control

// Receiver input pins
const int motorReceiverPin = 2;    // Digital pin for motor receiver input
const int turnReceiverPin = 3;     // Digital pin for turning receiver input

// Variables to store last received PWM values
int lastMotorPulseWidth = 0;
int lastTurnPulseWidth = 0;

void setup() {
 
  // Set motor control pins as outputs
  pinMode(motorIn1Pin, OUTPUT);
  pinMode(motorIn2Pin, OUTPUT);
  pinMode(motorIn3Pin, OUTPUT);
  pinMode(motorIn4Pin, OUTPUT);
/*  pinMode(motor1_LEN, OUTPUT);
  pinMode(motor1_REN, OUTPUT);
  pinMode(motor2_LEN, OUTPUT);
  pinMode(motor2_REN, OUTPUT);*/

      Break();
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
 /* digitalWrite(motor1_LEN, HIGH);
  digitalWrite(motor1_REN, HIGH);
  digitalWrite(motor2_LEN, HIGH);
  digitalWrite(motor2_REN, HIGH);*/

 // Read the pulse width from the motor receiver
  int motorPulseWidth = pulseIn(motorReceiverPin, HIGH);
  int turnPulseWidth = pulseIn(turnReceiverPin, HIGH);

  // Check if valid signals are received
  if (isValidSignal(motorPulseWidth, turnPulseWidth)) {
    // Store the last valid PWM values
    lastMotorPulseWidth = motorPulseWidth;
    lastTurnPulseWidth = turnPulseWidth;
    
    // Control the motor and turning
    controlMotorAndTurning(motorPulseWidth, turnPulseWidth);
  } else {
    // If no valid signal, stop the motors
    Break();
  }
  
  delay(50);  // Adjust delay as needed
}

bool isValidSignal(int motorPulseWidth, int turnPulseWidth) {
  // Check if both motor and turn pulse widths are within valid ranges
  return (motorPulseWidth >= 990 && motorPulseWidth <= 1995 &&
          turnPulseWidth >= 990 && turnPulseWidth <= 1995);
}


void controlMotorAndTurning(int motorPulseWidth, int turnPulseWidth) {
  // Map the pulse width to motor speed
  int motorSpeed = map(motorPulseWidth, 990, 1995, -255, 255); // Assuming full range PWM control

  // Map the pulse width to turning angle or direction
  int turnAngle = map(turnPulseWidth, 990, 1995, -255, 255); // Assuming a range from -90° to 90°

  Serial.print("Motor Speed: ");
  Serial.print(motorSpeed);
  Serial.print(" | Turn Angle: ");
  Serial.println(turnAngle);

  // Determine 
  //motor direction based on motorSpeed
   if (abs(motorSpeed) <= 15) {
    // Apply break
    
   Break();
  } 
  else if (motorSpeed >= 15) {
    // Move forward
    //moveForward(abs(motorSpeed));
    moveBackward(abs(motorSpeed));
  } 
  else {
    // Move backward
   // moveBackward(abs(motorSpeed));
   moveForward(abs(motorSpeed));
  }

  // Determine turning direction based on turnAngle
  if (turnAngle >= 15) {
    // Turn right
    turnRight(abs(turnAngle) );  // Adjust multiplier as needed for turning sensitivity
  } 
  else if (turnAngle <= -15) {
    // Turn left
    turnLeft(abs(turnAngle) );   // Adjust multiplier as needed for turning sensitivity
  } 
  else {
    // Straight or minimal turning
   // Break();  // Stop the motors if minimal or no turning required
  }
}

void moveForward(int speed) {
  // Both motors forward
  digitalWrite(motorIn1Pin, HIGH);
  digitalWrite(motorIn2Pin, LOW);
  digitalWrite(motorIn3Pin, HIGH);
  digitalWrite(motorIn4Pin, LOW);
}

void moveBackward(int speed) {
  // Both motors backward

  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, HIGH);
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, HIGH);
}

void turnLeft(int speed) {
  // Left motor backward, right motor forward
  digitalWrite(motorIn1Pin, LOW);   // Stop left motor
  digitalWrite(motorIn2Pin, HIGH);
  digitalWrite(motorIn3Pin, HIGH);
  digitalWrite(motorIn4Pin, LOW);   // Stop right motor
}

void turnRight(int speed) {
  // Left motor forward, right motor backward
  digitalWrite(motorIn1Pin, HIGH);
  digitalWrite(motorIn2Pin, LOW);   // Stop left motor
  digitalWrite(motorIn3Pin, LOW);   // Stop right motor
  digitalWrite(motorIn4Pin, HIGH);
}

void Break() {
  // Stop both motors
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, LOW);
  digitalWrite(motorIn3Pin, LOW);
  digitalWrite(motorIn4Pin, LOW);
}