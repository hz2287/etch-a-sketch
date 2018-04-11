/*
  ADXL3xx

  Reads an Analog Devices ADXL3xx accelerometer and communicates the
  acceleration to the computer. The pins used are designed to be easily
  compatible with the breakout boards from SparkFun, available from:
  http://www.sparkfun.com/commerce/categories.php?c=80

  The circuit:
  - analog 0: accelerometer self test
  - analog 1: z-axis
  - analog 2: y-axis
  - analog 3: x-axis
  - analog 4: ground
  - analog 5: vcc

  created 2 Jul 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ADXL3xx
*/

// these constants describe the pins. They won't change:
//const int groundpin = 18;             // analog input pin 4 -- ground
//const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

int x = 0;
int y = 0;
int z = 0;
int newX = 0;
int newY = 0;
String message = "";


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // initialize the serial communications:
  Serial.begin(115200);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  //pinMode(groundpin, OUTPUT);
  //pinMode(powerpin, OUTPUT);
  //digitalWrite(groundpin, LOW);
  //digitalWrite(powerpin, HIGH);
}

void loop() {
  // print the sensor values:
  x = analogRead(xpin);
  // print a tab between values:
  y = analogRead(ypin);
  // print a tab between values:
  z = analogRead(zpin);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print('x');
  lcd.setCursor(7,0);
  lcd.print('y');
  lcd.setCursor(12,0);
  lcd.print('z');
  lcd.setCursor(1,1);
  lcd.print(x);
  lcd.setCursor(6,1);
  lcd.print(y);
  lcd.setCursor(11,1);
  lcd.print(z);
  newX = map(constrain(x, 270, 400), 270, 400, 0, 1023);
  newY = map(constrain(y, 270, 400), 270, 400, 0, 1023);
  message = String(newX) + "," + String(newY);
  Serial.println(message);
  
  // delay before next reading:
  delay(500);
}
