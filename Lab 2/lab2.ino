/**
* Ryan Fitzgerald (7233237)
* Cody McCoshen (7208960)
* SEG4145
* Laboratory 2
* lab2.ino
* This file is responsible for processing sensor data by reading and processing the
* wheel encoder data in real-time. It also controls the movements of the robot in a precise
* manner while following a predefined path
*
*/

#include <SoftwareSerial.h>
#include <stdio.h>

// Macros
#define LEFT_FORWARD()    analogWrite(45, 191.5);
#define LEFT_BACKWARD()   analogWrite(45, 10);
#define LEFT_STOP()     analogWrite(45, 0);
#define RIGHT_FORWARD()   analogWrite(8, 10);
#define RIGHT_BACKWARD()  analogWrite(8, 191.5);
#define RIGHT_STOP()    analogWrite(8, 0);

// Global variables
int flashing;
SoftwareSerial LCD = SoftwareSerial(0, 18); // Initialize the LCD screen

// the setup function runs once when you press reset or power the board
void setup() {
    // Assign all required pins
    pinMode(13, OUTPUT); // LED
    pinMode(45, OUTPUT); // Left Motor
    pinMode(8, OUTPUT); // Right Motor
    pinMode(49, INPUT); // Left wheel sensor
    pinMode(48, INPUT); // Right wheel sensor

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

    // --- Path ---
    printPath("Start Path");
    doPath();
  
}

/**
* Clears all characters from the LCD screen.
* @name clearLCD
* @return (void)
*/
void clearLCD() {
    LCD.write(0xFE);  // Put the LCD screen in command mode.
    LCD.write(0x01);  // Clear the LCD screen.
    delay(10);
}

/**
* Prints path to the LCD screen.
* @name printPath
* @param path the message that will be printed
* @return (void)
*/
void printPath(char* path) {
    // Clear the LCD
    clearLCD();

    // Put the LCD screen in command mode.
    LCD.write(0xFE);

    // Get length
    int wordLen = strlen(path);

    // Set cursor to first row, first column
    LCD.write(((16-wordLen)/2) + 0*64 + 128);

    // Print the path
    LCD.print(path);
    delay(3000);
}

/**
* Prints a message to the LCD screen.
* @name printMessage
* @param msg the message that will be printed
* @return (void)
*/
void printMessage(char* word1, char* word2) {
    // Clear the LCD
    clearLCD();

    // Put the LCD screen in command mode.
    LCD.write(0xFE);

    // Get word1 length
    int word1Len = strlen(word1);

    // Set cursor to first row, first column
    LCD.write(((16-word1Len)/2) + 0*64 + 128);

    // Print the message
    LCD.print(word1);

    // If there is another word
    if (word2 != 0) {
        // Put the LCD screen in command mode.
        LCD.write(0xFE);

        // Get word1 length
        int word2Len = strlen(word2);
    
        // Set cursor to first row, first column
        LCD.write(((16-word2Len)/2) + 1*64 + 128);
        
        // Print the message
        LCD.print(word2);
    }
    
    delay(10);
}

/**
* Flashes the light every second for num amount of time.
* @name flashLight
* @param num number of seconds that the light will be flashing
* @return (void)
*/
void flashLight(int num) {
    for (flashing = 0; flashing < num; flashing++) {
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

/**
* Performs an action for a predefined number of "ticks"
* @name performAction
* @param ticks number of wheel ticks that must be processed
* @return (void)
*/
void performAction(int ticks) {
    int times = 0;
    int oldPulse = NULL;
    int newPulse = NULL;

    while (times < ticks) {

      oldPulse = newPulse;
      newPulse = digitalRead(48);

      if (newPulse != oldPulse) {
        times++;
      }
           
    }
}

/**
* Stops the robot. A delay is provided to determine how long
* the robot will remain in this state.
* @name stopMotor
* @param duration number of milliseconds that the robot will remain in this state
* @return (void)
*/
void stopMotor(int duration) {
    LEFT_STOP();
    RIGHT_STOP();
    performAction(duration);
}

/**
* Moves the robot forward. A delay is provided to determine how long
* the robot will remain in this state.
* @name moveForward
* @param duration number of milliseconds that the robot will remain in this state
* @return (void)
*/
void moveForward(int duration) {
    LEFT_FORWARD();
    RIGHT_FORWARD();
    performAction(duration);
}

/**
* Moves the robot backward. A delay is provided to determine how long
* the robot will remain in this state.
* @name moveBackward
* @param duration number of milliseconds that the robot will remain in this state
* @return (void)
*/
void moveBackward(int duration) {
    LEFT_BACKWARD();
    RIGHT_BACKWARD();
    performAction(duration);
}

/**
* Turns the robot left. A delay is provided to determine how long
* the robot will remain in this state.
* @name turnLeft
* @param duration number of milliseconds that the robot will remain in this state
* @return (void)
*/
void turnLeft(int duration) {
    LEFT_BACKWARD();
    RIGHT_FORWARD();
    performAction(duration);
}

/**
* Turns the robot right. A delay is provided to determine how long
* the robot will remain in this state.
* @name turnRight
* @param duration number of milliseconds that the robot will remain in this state
* @return (void)
*/
void turnRight(int duration) {
    LEFT_FORWARD();
    RIGHT_BACKWARD();
    performAction(duration);
}

/**
* Provides the commands to make the robot perform Path 3.
* @name doPath
* @return (void)
*/
void doPath(){
  
    // Move straight
    printMessage("Moving", "Forward");
    moveForward(128);

    // Turn Right
    printMessage("Turning", "Right");
    turnRight(45);

    // Move straight
    printMessage("Moving", "Forward");
    moveForward(128);

    // Turn right
    printMessage("Turning", "Right");
    turnRight(45);

    // Move straight
    printMessage("Moving", "Forward");
    moveForward(192);

    // Turn right
    printMessage("Turning", "Right");
    turnRight(64);

    // Move straight
    printMessage("Moving", "Forward");
    moveForward(192);

    // Turn Right
    printMessage("Turning", "Right");
    turnRight(64);

    // Move straight
    printMessage("Moving", "Forward");
    moveForward(128);

    // Turn 45 Left
    printMessage("Turning", "Left");
    turnLeft(32);

    // Move Straight
    printMessage("Moving", "Forward");
    moveForward(64);
    
    // Turn left 135
    printMessage("Turning", "Left");
    turnLeft(96);

    // Move straight
    printMessage("Moving", "Forward");
    moveForward(256);

    // Turn left
    printMessage("Turning", "Left");
    turnLeft(64);
    
    // Move straight
    printMessage("Moving", "Forward");
    moveForward(128);

    // Turn left
    printMessage("Turning", "Left");
    turnLeft(64);

     // Move straight
    printMessage("Moving", "Forward");
    moveForward(128);
    
    // Stop motor for 5s
    printMessage("Stopped", 0);
    stopMotor(64);
}
