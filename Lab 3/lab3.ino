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
#define LEFT_STOP()       analogWrite(45, 0);
#define RIGHT_FORWARD()   analogWrite(8, 10); // 100
#define RIGHT_BACKWARD()  analogWrite(8, 191.5);
#define RIGHT_STOP()      analogWrite(8, 0);

// Global variables
int flashing;
int turning = 0;
long time1;
long distance;
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

    moveForward(115);
    stopMotor(1000);
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
* Continues wheel motor from where it left off
* @name continueOperation
* @return (void)
*/
void adjustSpeed(int motor) {
    
    if (motor == 45) {
      RIGHT_FORWARD();
      analogWrite(motor, 150);
    } else {
      LEFT_FORWARD();
      analogWrite(motor, 100);
    }
    
}

void performSonar(){
      // put your main code here, to run repeatedly:
    pinMode(22, OUTPUT); // Output Sonar sensor
    digitalWrite(22,LOW);
    //Wait for 2 microsecs
    delay(0.002);
    digitalWrite(22,HIGH);
    //Wait for 5 microsecs
    delay(0.005);
    //Write low
    digitalWrite(22,LOW);
    
    pinMode(22, INPUT); // Input Sonar sensor
    // Read duration of the pulse
    time1 = pulseIn(22, HIGH);
  
    distance = time1/(29*2);
    delay(10);
}

void collisionAvoid(){
  
}

/**
* Performs an action for a predefined number of "ticks"
* @name performAction
* @param ticks number of wheel ticks that must be processed
* @return (void)
*/
void performAction(int ticks) {
    int timeLeft = 0;
    int timeRight = 0;
    int oldPulseLeft = NULL;
    int newPulseLeft = NULL;
    int oldPulseRight = NULL;
    int newPulseRight = NULL;
    int valid = 0;

    while (valid == 0) {
        performSonar();

        // Read left motor  sensor
        oldPulseLeft = newPulseLeft;
        newPulseLeft = digitalRead(48);
        
        // Read right motor sensor
        oldPulseRight = newPulseRight;
        newPulseRight = digitalRead(49);

        if(distance <= 10){
          stopMotor(5000);
          //collisionAvoid();
        }
        
        // If new tick, increment left time
        if (newPulseLeft != oldPulseLeft) {
            timeLeft++;
        }
        
        // If new tick, increment right time
        if (newPulseRight != oldPulseRight) {
            timeRight++;
        }

        if (turning != 1) {
          
          // Check if sensors are equal or not
          if (timeLeft > timeRight) {
              adjustSpeed(45);
          } else if (timeRight > timeLeft) {
              adjustSpeed(8);
          }
        }

        if (timeLeft >= ticks && timeRight >= ticks) {
          valid = 1;
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
    turning = 0;
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
    turning = 0;
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
    turning = 0;
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
    turning = 1;
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
    turning = 1;
    performAction(duration);
}

