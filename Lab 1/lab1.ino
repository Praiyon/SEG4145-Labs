#include <SoftwareSerial.h>

// Global variables
int pin_value = 0;
int flashing = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // led
  pinMode(13, OUTPUT);
  
  int lcd_pin_number = 18;
  SoftwareSerial LCD = SoftwareSerial(0, lcd_pin_number);
  LCD.begin(9600);   
  LCD.write(0xFE);  // Put the LCD screen in command mode.
  LCD.write(0x01);  // Clear the LCD screen.
  delay(10);

  
  LCD.write(0xFE);  // Put the LCD screen in command mode.
  LCD.write(5 + 0*64 + 128);
  delay(10);        // Delay operation for 10 ms
  LCD.print("7233237");
  delay(10);
  LCD.write(0xFE);  // Put the LCD screen in command mode.
  LCD.write(5 + 1*64 + 128);
  LCD.print("7208960");
  delay(10);
  //
  while (flashing < 5) {
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    flashing++;
  }
  LCD.write(0xFE);  // Put the LCD screen in command mode.
  LCD.write(0x01);  // Clear the LCD screen.
  delay(10);
  // 
  pinMode(45, OUTPUT);
  pinMode(8, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  // --- Path 1 ---
  
  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Turn left
  analogWrite(45, 10);
  analogWrite(8, 10);
  delay(1000);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Turn right
  analogWrite(45, 191.5);
  analogWrite(8, 191.5);
  delay(600);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Turn right
  analogWrite(45, 191.5);
  analogWrite(8, 191.5);
  delay(600);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Turn left
  analogWrite(45, 10);
  analogWrite(8, 10);
  delay(1000);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Stop motor for 5s
  analogWrite(45, 0);
  analogWrite(8, 0);
  delay(5000);

  // --- Path 2 ---
  
  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Turn right
  analogWrite(45, 191.5);
  analogWrite(8, 191.5);
  delay(600);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Turn left
  analogWrite(45, 10);
  analogWrite(8, 10);
  delay(1500);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(2500);

  // Turn right
  analogWrite(45, 191.5);
  analogWrite(8, 191.5);
  delay(900);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Turn left
  analogWrite(45, 10);
  analogWrite(8, 10);
  delay(1000);

  // Move straight
  analogWrite(45, 191.5);
  analogWrite(8, 10);
  delay(1000);

  // Stop motor for 5s
  analogWrite(45, 0);
  analogWrite(8, 0);
  delay(5000);

}
