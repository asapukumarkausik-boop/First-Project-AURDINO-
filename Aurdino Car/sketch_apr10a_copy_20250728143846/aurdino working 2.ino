#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

// Motor connections
AF_DCMotor rightBack(1);  // M1
AF_DCMotor rightFront(2); // M2
AF_DCMotor leftFront(3);  // M3
AF_DCMotor leftBack(4);   // M4

// Ultrasonic sensor
#define TRIGGER_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Servo
Servo lookServo;
#define SERVO_PIN 10

// Constants
#define OBSTACLE_DISTANCE 30  // cm to trigger avoidance
#define SAFE_DISTANCE 50      // cm considered safe
#define SCAN_LEFT 150         // left scan angle
#define SCAN_RIGHT 30         // right scan angle
#define SCAN_CENTER 90        // center position
#define MOVE_DELAY 500        // ms to move after decision
#define SCAN_DELAY 300        // ms for servo movement
#define BACKUP_TIME 800       // ms to move backward
#define TURN_TIME 600         // ms to turn

// Speed settings
#define NORMAL_SPEED 200
#define SLOW_SPEED 150
#define TURN_SPEED 180

void setup() {
  Serial.begin(9600);
  
  // Initialize motors
  setAllSpeeds(NORMAL_SPEED);
  
  // Initialize servo
  lookServo.attach(SERVO_PIN);
  centerServo();
}

void loop() {
  int distance = checkDistance();
  
  if (distance > OBSTACLE_DISTANCE) {
    moveForward();
  } else {
    avoidObstacle();
  }
}

void avoidObstacle() {
  Serial.println("=== OBSTACLE DETECTED ===");
  stopMotors();
  
  // Step 1: Move backward to create space
  moveBackward(BACKUP_TIME);
  
  // Step 2: Scan environment
  int leftDist = scanArea(SCAN_LEFT);
  int rightDist = scanArea(SCAN_RIGHT);
  centerServo();
  
  // Step 3: Decide action based on scan results
  if (leftDist > rightDist && leftDist > SAFE_DISTANCE) {
    Serial.println("Turning LEFT - More space available");
    turnLeft(TURN_TIME);
  } 
  else if (rightDist > SAFE_DISTANCE) {
    Serial.println("Turning RIGHT - More space available");
    turnRight(TURN_TIME);
  }
  else if (leftDist > rightDist) {
    Serial.println("Turning LEFT - Less worse option");
    turnLeft(TURN_TIME * 1.5); // Longer turn for tight space
  }
  else {
    Serial.println("Turning RIGHT - Less worse option");
    turnRight(TURN_TIME * 1.5); // Longer turn for tight space
  }
  
  // Step 4: Move forward after turning
  moveForward(MOVE_DELAY);
}

// === Movement Functions === //

void moveForward(int duration = 0) {
  Serial.println("Moving FORWARD");
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
  if (duration > 0) {
    delay(duration);
    stopMotors();
  }
}

void moveBackward(int duration) {
  Serial.println("Moving BACKWARD");
  setAllSpeeds(SLOW_SPEED);
  rightBack.run(BACKWARD);
  rightFront.run(BACKWARD);
  leftFront.run(BACKWARD);
  leftBack.run(BACKWARD);
  delay(duration);
  stopMotors();
  setAllSpeeds(NORMAL_SPEED);
}

void turnLeft(int duration) {
  Serial.println("Turning LEFT");
  setAllSpeeds(TURN_SPEED);
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(BACKWARD);
  leftBack.run(BACKWARD);
  delay(duration);
  stopMotors();
  setAllSpeeds(NORMAL_SPEED);
}

void turnRight(int duration) {
  Serial.println("Turning RIGHT");
  setAllSpeeds(TURN_SPEED);
  rightBack.run(BACKWARD);
  rightFront.run(BACKWARD);
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
  delay(duration);
  stopMotors();
  setAllSpeeds(NORMAL_SPEED);
}

void stopMotors() {
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE);
}

// === Sensor Functions === //

int checkDistance() {
  delay(50); // Stabilize sensor
  unsigned int uS = sonar.ping();
  int cm = sonar.convert_cm(uS);
  if (cm == 0) cm = MAX_DISTANCE;
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");
  return cm;
}

int scanArea(int angle) {
  lookServo.write(angle);
  delay(SCAN_DELAY);
  int distance = checkDistance();
  Serial.print("Scan at ");
  Serial.print(angle);
  Serial.print("°: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void centerServo() {
  lookServo.write(SCAN_CENTER);
  delay(SCAN_DELAY/2);
}

// === Utility Functions === //

void setAllSpeeds(int speed) {
  rightBack.setSpeed(speed);
  rightFront.setSpeed(speed);
  leftFront.setSpeed(speed);
  leftBack.setSpeed(speed);
}