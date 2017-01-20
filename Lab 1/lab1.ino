/**
* Ryan Fitzgerald (7233237)
* Cody McCoshen (7208960)
* SEG4145
* Laboratory 1
* lab1.ino
* This file is responsible for making the robot perform Path 1 and
* Path 2 detailed in the Lab manual for Laboratory 1. The robot
* will print the command its performing on its LCD screen.
*/

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
    doPath1();

    // --- Path 2 ---
    doPath2();
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
* Prints a message to the LCD screen.
* @name printMessage
* @param msg the message that will be printed
* @return (void)
*/
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
* Stops the robot. A delay is provided to determine how long
* the robot will remain in this state.
* @name stopMotor
* @param duration number of milliseconds that the robot will remain in this state
* @return (void)
*/
void stopMotor(int duration) {
    LEFT_STOP();
    RIGHT_STOP();
    delay(duration);
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
    delay(duration);
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
    delay(duration);
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
    delay(duration);
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
    delay(duration);
}

/**
* Provides the commands to make the robot perform Path 1.
* @name doPath1
* @return (void)
*/
void doPath1(){
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
}

/**
* Provides the commands to make the robot perform Path 2.
* @name doPath2
* @return (void)
*/
void doPath2(){
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
