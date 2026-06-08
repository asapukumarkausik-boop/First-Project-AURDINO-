# Arduino Obstacle Avoiding Car 🚗

## Overview
The Arduino Obstacle Avoiding Car is an autonomous robotic vehicle designed to navigate its surroundings without human intervention. The system uses an ultrasonic sensor to detect obstacles in front of the vehicle and automatically changes its direction to avoid collisions.

This project demonstrates the practical application of embedded systems, sensor integration, motor control, and basic autonomous navigation using Arduino.

---

## Features

- Automatic obstacle detection
- Collision avoidance system
- Real-time distance measurement
- Autonomous navigation
- Servo-based scanning mechanism
- DC motor movement control
- Low-cost and beginner-friendly robotics project

---

## Components Used

| Component | Quantity |
|------------|-----------|
| Arduino Uno | 1 |
| Ultrasonic Sensor (HC-SR04) | 1 |
| Servo Motor | 1 |
| Motor Driver Shield | 1 |
| DC Motors | 4 |
| Wheels | 4 |
| Battery Pack | 1 |
| Chassis | 1 |
| Connecting Wires | As Required |

---

## Working Principle

1. The ultrasonic sensor continuously measures the distance to nearby objects.
2. If no obstacle is detected within the predefined range, the car moves forward.
3. When an obstacle is detected, the car stops.
4. The servo motor rotates the ultrasonic sensor to scan both left and right directions.
5. The Arduino compares the available space on both sides.
6. The car turns toward the direction with more free space.
7. The process repeats continuously, allowing autonomous navigation.

---

## Technologies Used

- Arduino IDE
- Embedded C/C++
- HC-SR04 Sensor Library
- Servo Library

---

## Circuit Connections

### Ultrasonic Sensor

| HC-SR04 Pin | Arduino Pin |
|-------------|-------------|
| VCC | 5V |
| GND | GND |
| Trigger | A0 |
| Echo | A1 |

### Servo Motor

| Servo Pin | Arduino Pin |
|------------|-------------|
| Signal | SER1 |
| VCC | 5V |
| GND | GND |

### Motors

The four DC motors are connected to the motor driver shield outputs:

- M1
- M2
- M3
- M4

---

## Applications

- Autonomous robots
- Smart vehicle prototypes
- Educational robotics projects
- Obstacle detection systems
- Robotics competitions
- Embedded systems learning

---

## Future Improvements

- Bluetooth control mode
- Mobile application integration
- Voice command support
- Line following functionality
- GPS navigation
- Camera-based object detection
- Machine learning integration

---

## Learning Outcomes

Through this project, I gained practical experience in:

- Arduino programming
- Sensor interfacing
- Motor control
- Embedded systems
- Robotics fundamentals
- Problem-solving and debugging

---

## Project Images

Add images of your car here.

Example:

![Obstacle Avoiding Car](images/car.jpg)

---

## Author

Kausik

Final Year Student

Passionate about Robotics, Python Development, Android Development, and Problem Solving.

---

## License

This project is developed for educational and learning purposes.
