/**
* Ryan Fitzgerald (7233237)
* Cody McCoshen (7208960)
* SEG4145
* Laboratory 3
* lab3.ino
* This file is responsible for processing sensor data by reading and processing the
* wheel encoder data in real-time. It also controls the movements of the robot in a precise
* manner while following a predefined path
*
*/

#include <SoftwareSerial.h>
#include <stdio.h>
#include <Wire.h>

// Macros
#define LEFT_FORWARD()    analogWrite(45, 191.5);
#define LEFT_BACKWARD()   analogWrite(45, 10);
#define LEFT_STOP()       analogWrite(45, 0);
#define RIGHT_FORWARD()   analogWrite(8, 10);
#define RIGHT_BACKWARD()  analogWrite(8, 191.5);
#define RIGHT_STOP()      analogWrite(8, 0);
#define TEMPSENSOR        0x68

// Global variables
int flashing, checkSonar;
int turning = 0;
long pingDuration;
long distance;
byte temperatureData;
SoftwareSerial LCD = SoftwareSerial(0, 18); // Initialize the LCD screen
int reg = 0x01; // For ambient temperature reader

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
  
    // Join I2C bus for ambient temp
    Wire.begin(); 
}

// the loop function runs over and over again forever
void loop() {
    // Set check sonar to 1
    checkSonar = 1;

    // Move forward 1 tile
    printMessage("Moving", "Forward");
    moveForward(50);

    // Stop for 1s
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
* Prints a message to the LCD screen.
* @name printMessage
* @param word1 word on first line, word2 word of second line
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
    
    // Delay for 10 milliseconds
    delay(10);
}

/**
* Prints temperature to LCD Screen
* @name printTemperature
* @param word1 word on first line, word2 word of second line
* @return (void)
*/
void printTemperature(char* word1, byte word2) {
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
	
    // Delay for 10 milliseconds
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
* Adjust the speed of the wheels
* @name adjustSpeed
* @param motor number of motor
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

/**
* Read the sonar results and calculates the resulting distance
* @name performSonar
* @return (void)
*/
void performSonar(){
  
    // Output Sonar sensor
    pinMode(22, OUTPUT); 
  
    // Write low value to pin
    digitalWrite(22, LOW);
  
    //Wait for 2 microsecs
    delay(0.002);
  
    // Write high value to pin
    digitalWrite(22, HIGH);
  
    //Wait for 5 microsecs
    delay(0.005);
  
    //Write low value to pin
    digitalWrite(22, LOW);
  
    // Input Sonar sensor
    pinMode(22, INPUT);
  
    // Read duration of the pulse
    pingDuration = pulseIn(22, HIGH);
  
    // Calculate distance
    distance = pingDuration / (29*2);
    
    // Delay 10 milliseconds
    delay(10);
}

/**
* Series of collision avoidance events that are run when the robot 
* comes 10cm or less to an object in front of it
* @name collisionAvoid
* @return (void)
*/
void collisionAvoid(){
  
    // Set checkSonar to 0
    checkSonar = 0;

    // Stop the motor
    stopMotor(10);

    // Read the temperature
    readTemp();

    // Print the temperature
    printTemperature("Temperature", temperatureData);

    // Delay for 5s
    delay(5000);  

    // Move the robot back 1 tile
    printMessage("Moving", "Backward");
    moveBackward(115);

    // Rotate robot 90 degrees cw
    printMessage("Turning", "Right");
    turnRight(55);

    // Move forward 2 tiles
    printMessage("Moving", "Forward");
    moveForward(230);

    // Rotate robot 90 degrees ccw
    printMessage("Turning", "Left");
    turnLeft(20);

    // Returns and continues forward movement
 
}

/**
* Performs an action for a predefined number of "ticks"
* @name actionLength
* @param ticks number of wheel ticks that must be processed
* @return (void)
*/
void actionLength(int ticks) {
    int timeLeft = 0;
    int timeRight = 0;
    int oldPulseLeft = NULL;
    int newPulseLeft = NULL;
    int oldPulseRight = NULL;
    int newPulseRight = NULL;
    int valid = 0;

    while (valid == 0) {
    
        // If checking sonar is required
        if (checkSonar == 1) {
          
            // Check sonar
            performSonar();

            // Check if distance is less than or equal to 10
            if (distance <= 10.0) {
            collisionAvoid();
            }
          
        }
        
        // Read left motor  sensor
        oldPulseLeft = newPulseLeft;
        newPulseLeft = digitalRead(48);
        
        // Read right motor sensor
        oldPulseRight = newPulseRight;
        newPulseRight = digitalRead(49);
        
        // If new tick, increment left time
        if (newPulseLeft != oldPulseLeft) {
            timeLeft++;
        }
        
        // If new tick, increment right time
        if (newPulseRight != oldPulseRight) {
            timeRight++;
        }

        // If the robot is not currently turning
        if (turning != 1) {
          
          // Check if sensors are equal or not
          if (timeLeft > timeRight) {
              adjustSpeed(45);
          } else if (timeRight > timeLeft) {
              adjustSpeed(8);
          }
        }

        // Set valid flag to true if both are done		
        if (timeLeft >= ticks && timeRight >= ticks) {
          valid = 1;
        }
    }
}

/**
* Reads the ambient temperature
* @name readTemp
* @return (void)
*/
void readTemp() {
    Wire.beginTransmission(TEMPSENSOR);
    Wire.write(reg); // Indicate temperature value to read
    Wire.endTransmission();
    Wire.requestFrom(TEMPSENSOR, 1); // Request data
    while(Wire.available() < 1); // Wait for data
    temperatureData = Wire.read(); // Store temperature value
    delay(50); // Delay 50 ms if values are read in a loop
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
    actionLength(duration);
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
    turning = 1; // Flag so wheels don't get adjusted
    actionLength(duration);
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
    actionLength(duration);
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
    actionLength(duration);
}

