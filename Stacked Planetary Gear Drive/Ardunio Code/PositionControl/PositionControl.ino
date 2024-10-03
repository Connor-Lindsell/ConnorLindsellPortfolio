/*________________________________________________________________________________________________*/
/*  
  PostionControl
  
  Stacked Planetary Gear Drive Actuator Position Control
  Description of code:
  This code controls a stepper motor that operates a stacked planetary gear system. The motor
  movement is controlled via a step and direction driver, with the user providing input through 
  the Serial Monitor. The code prompts the user to input the angle of rotation (in degrees), 
  the direction of rotation (clockwise or counterclockwise), and the speed (in microseconds per 
  step). Based on this input, the motor rotates to the specified angle at the given speed. 

  Key features:
  1. Angle-based rotation: The motor rotates to a specified angle based on the user's input.
     The number of steps needed is calculated based on the degrees per step for the motor, 
     ensuring precise angular control.
     
  2. Direction control: The user can specify whether the motor should rotate clockwise ('C') 
     or counterclockwise ('A'). The direction pin is set accordingly.
     
  3. Speed control: The user defines the speed of the motor in terms of delay between steps 
     (in microseconds), allowing control over how fast the motor rotates.
  
  Date: 5/08/2024
  Created By: Connor Lindsell

*/
/*________________________________________________________________________________________________*/


const int stepPin = 2;       // Pin connected to the step pin of the driver
const int dirPin = 5;        // Pin connected to the direction pin of the driver
const int stepsPerRevolution = 5000; // Number of steps per revolution for the motor
const float degreesPerStep = 360.0 / stepsPerRevolution; // Degrees per step for the motor

int speed = 500; // Speed of the motor in microseconds (lower value means higher speed)
float angle = 0; // Angle to rotate in degrees
bool clockwise = true; // Direction of rotation

void setup() {
  // Set the pins as outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  // Initialize Serial Monitor for input
  Serial.begin(9600);
  
  // Print prompts to the Serial Monitor
  Serial.println("Enter the angle to rotate (in degrees), direction (C for clockwise, A for counterclockwise), and speed (in microseconds per step):");
  Serial.println("Format: angle direction speed");
  Serial.println("Example: 160 C 500");
}

void loop() {
  // Check if data is available on the Serial Monitor
  if (Serial.available() > 0) {
    // Read the entire input line
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    // Parse the input
    int firstSpace = input.indexOf(' ');
    int secondSpace = input.lastIndexOf(' ');

    if (firstSpace > 0 && secondSpace > firstSpace) {
      // Extract the angle
      angle = input.substring(0, firstSpace).toFloat();
      
      // Extract the direction
      char direction = input.substring(firstSpace + 1, firstSpace + 2).charAt(0);
      
      // Extract the speed
      speed = input.substring(secondSpace + 1).toInt();

      // Print debug messages
      Serial.print("Angle: ");
      Serial.println(angle);
      Serial.print("Direction: ");
      Serial.println(direction);
      Serial.print("Speed: ");
      Serial.println(speed);
      
      // Set the direction based on input
      if (direction == 'C' || direction == 'c') {
        clockwise = true;
      } else if (direction == 'A' || direction == 'a') {
        clockwise = false;
      }

      // Calculate the number of steps for the given angle
      int steps = abs(angle / degreesPerStep);

      // Set the direction pin
      if (clockwise) {
        digitalWrite(dirPin, HIGH);
      } else {
        digitalWrite(dirPin, LOW);
      }

      // Rotate the motor
      for (int i = 0; i < steps; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }
      
      // Print completion message
      Serial.println("Rotation complete.");
    } else {
      Serial.println("Invalid input. Please enter the angle, direction, and speed in the format: angle direction speed");
    }

    // Print prompts again for next input
    Serial.println("Enter the angle to rotate (in degrees), direction (C for clockwise, A for counterclockwise), and speed (in microseconds per step):");
    Serial.println("Format: angle direction speed");
    Serial.println("Example: 160 C 500");
  }
}

