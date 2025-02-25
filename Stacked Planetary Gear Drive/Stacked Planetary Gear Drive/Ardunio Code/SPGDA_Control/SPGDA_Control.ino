/*________________________________________________________________________________________________*/
/*
  SPGDA_Control

  Stacked Planetary Gear Drive Actuator Control
  Description of code:
  This code controls a stepper motor through a stacked planetary gear system using a step and 
  direction driver. It offers three different types of motor movements selectable via the 
  Serial Monitor:

  1. Move2Angle: This mode rotates the motor to a specified angle in a chosen direction
      (clockwise or counterclockwise) at a user-defined speed. The number of steps needed 
      to reach the angle is calculated based on the steps per revolution and the specified angle.
      
  2. RevolutionForwardAndBack: This mode moves the motor forward by a user-defined number 
      of revolutions and then returns it to its original position. Both the number of revolutions 
      and speed are input through the Serial Monitor.
      
  3. Wave: In this mode, the motor performs a quick back-and-forth motion for a specified number 
      of cycles, simulating a "waving" action. The number of wave cycles and speed are input 
      by the user.
  
  Date: 30/09/2024
  Created By: Connor Lindsell

*/
/*________________________________________________________________________________________________*/


const int stepPin = 2;       // Pin connected to the step pin of the driver
const int dirPin = 5;        // Pin connected to the direction pin of the driver
const int stepsPerRevolution = 5000; // Number of steps per revolution for the motor
const float degreesPerStep = 360.0 / stepsPerRevolution; // Degrees per step for the motor

int speed = 500;              // Speed of the motor in microseconds (lower value means higher speed)
float angle = 0;              // Angle to rotate in degrees
bool clockwise = true;        // Direction of rotation

void setup() {
  // Set the pins as outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  // Initialize Serial Monitor for input
  Serial.begin(9600);
  
  // Print the movement options to the Serial Monitor
  Serial.println("Choose movement type:");
  Serial.println("1. Move2Angle");
  Serial.println("2. RevolutionForwardAndBack");
  Serial.println("3. Wave");
}

void loop() {
  // Check if data is available on the Serial Monitor
  if (Serial.available() > 0) {
    // Read the entire input line
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Check for movement type input
    if (input == "1") {
      move2Angle();
    } else if (input == "2") {
      revolutionForwardAndBack();
    } else if (input == "3") {
      wave();
    } else {
      Serial.println("Invalid option. Please enter 1, 2, or 3.");
    }
  }
}

// Move to a specific angle
void move2Angle() {
  Serial.println("Enter the angle, direction (C/A), and speed:");

  // Wait for input from the user
  while (Serial.available() == 0) {}

  String input = Serial.readStringUntil('\n');
  input.trim();

  // Parse input for angle, direction, and speed
  int firstSpace = input.indexOf(' ');
  int secondSpace = input.lastIndexOf(' ');

  if (firstSpace > 0 && secondSpace > firstSpace) {
    angle = input.substring(0, firstSpace).toFloat();
    char direction = input.substring(firstSpace + 1, firstSpace + 2).charAt(0);
    speed = input.substring(secondSpace + 1).toInt();

    // Set the direction based on input
    clockwise = (direction == 'C' || direction == 'c');
    digitalWrite(dirPin, clockwise ? HIGH : LOW);

    // Calculate the number of steps and rotate
    int steps = abs(angle / degreesPerStep);
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed);
    }
    Serial.println("Rotation complete.");
  } else {
    Serial.println("Invalid input. Try again.");
  }
}

// Move forward a number of revolutions and back
void revolutionForwardAndBack() {
  Serial.println("Enter the number of revolutions and speed:");

  // Wait for input from the user
  while (Serial.available() == 0) {}

  String input = Serial.readStringUntil('\n');
  input.trim();

  // Parse input for revolutions and speed
  int spaceIndex = input.indexOf(' ');

  if (spaceIndex > 0) {
    int revolutions = input.substring(0, spaceIndex).toInt();
    speed = input.substring(spaceIndex + 1).toInt();

    int steps = revolutions * stepsPerRevolution;

    // Move forward
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed);
    }

    // Move back
    digitalWrite(dirPin, LOW);
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed);
    }
    Serial.println("Forward and back movement complete.");
  } else {
    Serial.println("Invalid input. Try again.");
  }
}

// Wave the motor back and forth
void wave() {
  Serial.println("Enter the number of waves and speed:");

  // Wait for input from the user
  while (Serial.available() == 0) {}

  String input = Serial.readStringUntil('\n');
  input.trim();

  // Parse input for number of waves and speed
  int spaceIndex = input.indexOf(' ');

  if (spaceIndex > 0) {
    int waves = input.substring(0, spaceIndex).toInt();
    speed = input.substring(spaceIndex + 1).toInt();

    // Perform the wave motion
    for (int i = 0; i < waves; i++) {
      digitalWrite(dirPin, HIGH); // Move forward
      for (int j = 0; j < stepsPerRevolution / 4; j++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }

      digitalWrite(dirPin, LOW); // Move back
      for (int j = 0; j < stepsPerRevolution / 4; j++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }
    }
    Serial.println("Wave motion complete.");
  } else {
    Serial.println("Invalid input. Try again.");
  }
}
