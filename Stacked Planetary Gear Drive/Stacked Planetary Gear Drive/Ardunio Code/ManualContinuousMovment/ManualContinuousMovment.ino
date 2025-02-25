/*________________________________________________________________________________________________*/
/*  
  ManualContinuousMovment

  Stacked Planetary Gear Drive Actuator Control with Button Input
  Description of code:
  This code controls a stepper motor that drives a stacked planetary gear system using a step 
  and direction driver. The motor movement is triggered by a button press, allowing for manual 
  control of the motor’s movement. The motor rotates in a specified direction while the button 
  is held down and stops when the button is released. This provides a simple, intuitive way 
  to control motor movement for applications requiring user interaction.

  Key features:
  1. Button-Controlled Movement: The motor moves only when the button is pressed. The motor 
     stops rotating as soon as the button is released, allowing precise control of movement.
     
  2. Direction Control: The direction of rotation is defined by the `clockwise` variable. 
     By default, the motor rotates clockwise. The direction pin is configured accordingly.
     
  3. Speed Control: The speed of the motor is controlled by a delay between each step, defined 
     by the `speed` variable in microseconds. A lower value of `speed` results in faster rotation.
     
  4. Manual Override: The system provides flexibility for manual control, making it useful in 
     scenarios where step-by-step precision is important, or where the user needs to control 
     the motor intermittently.

  Application: 
  This code is ideal for applications where user intervention is required to control the motor, 
  such as positioning systems, robotic actuators, or motorized mechanisms that need manual 
  override functionality. The use of a stacked planetary gear system ensures high torque and 
  precise angular control.

  Date: 30/09/2024
  Created By: Connor Lindsell

*/
/*________________________________________________________________________________________________*/


const int stepPin = 2;       // Pin connected to the step pin of the driver
const int dirPin = 5;        // Pin connected to the direction pin of the driver
const int buttonPin = 8;     // Pin connected to the button
const int stepsPerRevolution = 5000; // Number of steps per revolution for the motor
const float degreesPerStep = 360.0 / stepsPerRevolution; // Degrees per step for the motor

int speed = 500;             // Speed of the motor in microseconds (lower value means higher speed)
float angle = 0;             // Angle to rotate in degrees
bool clockwise = true;       // Direction of rotation

void setup() {
  // Set the pins as outputs or inputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with an internal pull-up resistor
  
  // Set initial direction of rotation
  digitalWrite(dirPin, HIGH); // Set to clockwise initially
  
  // Initialize Serial Monitor for debugging (optional)
  Serial.begin(9600);
  Serial.println("Press and hold the button to move the motor.");
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    // If the button is pressed, move the motor
    moveMotor();
  }
}

// Function to move the motor
void moveMotor() {
  // Set the direction pin based on the desired rotation direction
  if (clockwise) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }

  // Rotate the motor by a single step while the button is pressed
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speed);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speed);
}
