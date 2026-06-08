#include <AFMotor.h>

#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 250
// sets max speed of DC motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 


AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

// ==== PDI VARIABLES ====
float Kp = 3.0;
float Kd = 2.0;
float Ki = 0.2;

float error = 0, lastError = 0, integral = 0;
int setPoint = 50; // Desired distance from obstacle in cm

void setup() {
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  distance = readPing();

  if(distance <= 30) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if(distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    // === PDI CONTROL LOGIC ===
    error = setPoint - distance;
    integral += error;
    float derivative = error - lastError;
    float controlSignal = (Kp * error) + (Kd * derivative) + (Ki * integral);

    // Clamp speed to avoid over/under-driving
    int speed = constrain(abs(controlSignal), 80, MAX_SPEED); 

    moveForwardPDI(speed);
    lastError = error;
  }
}

// === Custom move forward with dynamic speed ===
void moveForwardPDI(int speed) {
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD);     
  
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}

int lookRight() {
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft() {
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 
  
void moveForward() {
 if(!goesForward) {
    goesForward = true;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD); 
    motor4.run(BACKWARD);     
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);     
  delay(500);
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);      
} 
 
void turnLeft() {
  motor1.run(FORWARD);     
  motor2.run(FORWARD);  
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);   
  delay(500);
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
