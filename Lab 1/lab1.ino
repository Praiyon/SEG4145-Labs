#include <SoftwareSerial.h>
#include <stdio.h>

// Macros
#define LEFT_FORWARD()		analogWrite(45, 191.5);
#define LEFT_BACKWARD()		analogWrite(45, 10);
#define LEFT_STOP()			analogWrite(45, 0);
#define RIGHT_FORWARD()		analogWrite(8, 10);
#define RIGHT_BACKWARD()	analogWrite(8, 191.5);
#define RIGHT_STOP()		analogWrite(8, 0);

// Global variables
int flashing;

// the setup function runs once when you press reset or power the board
void setup() {
	
	// Assign all required pins
	pinMode(13, OUTPUT); // LED
	pinMode(45, OUTPUT); // Left Motor
	pinMode(8, OUTPUT); // Right Motor
  
	// Initialize the LCD screen
	SoftwareSerial LCD = SoftwareSerial(0, 18);
	
	// Asign LCD Port
	LCD.begin(9600);   
	
	// Clear LCD
	clearLCD();
  
	// Put the LCD screen in command mode.
	LCD.write(0xFE);  
	
	// Set cursor to approximately the middle of the LCD first row
	LCD.write(5 + 0*64 + 128);
	delay(10);
	
	// Print first student number
	LCD.print("7233237");
	delay(10);
	
	// Put the LCD screen in command mode.
	LCD.write(0xFE);  
	
	// Set cursor to approximately the middle of the LCD second row
	LCD.write(5 + 1*64 + 128);
	
	// Print the second student number
	LCD.print("7208960");
	delay(10);
  
	// Flash light for ~5s
	flashLight(5);
  
	// Clear LCD
	clearLCD();
  
}

// the loop function runs over and over again forever
void loop() {

  // --- Path 1 ---
  
  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Turn left
  printMessage("Turning Left");
  turnLeft(1000);

  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Turn right
  printMessage("Turning Right");
  turnRight(600);

  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Turn right
  printMessage("Turning Right");
  turnRight(600);

  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Turn left
  printMessage("Turning Left");
  turnLeft(1000);

  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Stop motor for 5s
  printMessage("Finish Path 1");
  stopMotor(5000);

  // --- Path 2 ---
  
  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Turn right
  printMessage("Turning Right");
  turnRight(600);

  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Turn left
  printMessage("Turning Left");
  turnLeft(1500);

  // Move straight
  printMessage("Moving Forward");
  moveForward(2500);

  // Turn right
  printMessage("Turning Right");
  turnRight(900);
  
  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Turn left
  printMessage("Turning Left");
  turnLeft(1000);

  // Move straight
  printMessage("Moving Forward");
  moveForward(1000);

  // Stop motor for 5s
  printMessage("Finish Path 2");
  stopMotor(5000);

}

// Clear LCD Screen
void clearLCD() {
	LCD.write(0xFE);  // Put the LCD screen in command mode.
	LCD.write(0x01);  // Clear the LCD screen.
	delay(10);
}

// Print a message
void printMessage(char* msg) {
	// Clear the LCD
	clearLCD();
	
	// Put the LCD screen in command mode.
	LCD.write(0xFE);
	
	// Set cursor to first row, first column
	LCD.write(0 + 0*64 + 128);
	
	// Print the message
	LCD.print(msg);
	delay(10);
}

// Flash light
void flashLight(int num) {
	for (flash = 0; flashing < num; flashing++) {
		// Wait for 1s
		delay(1000);
		
		// turn the LED on (HIGH is the voltage level)
		digitalWrite(13, HIGH);   
		
		// Wait for 0.01s
		delay(10);
		
		// turn the LED on (HIGH is the voltage level)
		digitalWrite(13, LOW);   
	}
}

// Stop the robot
void stopMotor(int duration) {
	LEFT_STOP();
	RIGHT_STOP();
	delay(duration);
}

// Move forward
void moveForward(int duration) {
	LEFT_FORWARD();
	RIGHT_FORWARD();
	delay(duration);
}

// Move backwards
void moveBackward(int duration) {
	LEFT_BACKWARD();
	RIGHT_BACKWARD();
	delay(duration);
}

// Turn left
void turnLeft(int duration) {
	LEFT_BACKWARD();
	RIGHT_FORWARD();
	delay(duration);
}

// Turn right
void turnRight(int duration) {
	LEFT_FORWARD();
	RIGHT_BACKWARD();
	delay(duration);
}