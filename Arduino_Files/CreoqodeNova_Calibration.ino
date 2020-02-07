#include <Servo.h>

#define ACTIVATED LOW

Servo NovaServo_1; // Head Movement - Front and Back
Servo NovaServo_2; // Head Rotation - Clockwise and Anticlockwise
Servo NovaServo_3; // Head Rotation - Up and Down
Servo NovaServo_4; // Whole Body Rotation - 2 axis
Servo NovaServo_5; // Head Movement - Up and Down

// Joystick connections
int joystick1_x = A9;
int joystick1_y = A11;
int joystick2_x = A13;
int joystick2_y = A15;

int joystick1_sw = 43;
int joystick2_sw = 45;

// Current values of the potentiometers and tactile switches.
int value1_x;
int value1_y;
int value2_x;
int value2_y;

int value1_sw;
int value2_sw;

// Creating variables for potentiometer filtering.
int value1_xF = 90;
int value1_yF = 110;
int value2_xF = 90;
int value2_yF = 100;

// By pressing the tactile switches, we will be increasing and decreasing one of the servo shaft angles.
int degree = 90;

// Potentiometer Readings
float filter1_x = 0.05;
float filter1_y = 0.05;
float filter2_x = 0.08;
float filter2_y = 0.08;

/**
   This is like the constructor, it runs first before all the other functions.
*/
void setup() {

  calibrate();

}

/**
   A repeating function that won't stop.
*/
void loop() {

  joystickCalibration();
  //movement();

}

/**
   Calibrates the mask to rotate towards a 90 degrees angle.
*/
void calibrate() {

  Serial.begin(9600);

  pinMode(joystick1_sw, INPUT_PULLUP);
  pinMode(joystick2_sw, INPUT_PULLUP);

  NovaServo_1.attach(32);
  NovaServo_2.attach(34);
  NovaServo_3.attach(36);
  NovaServo_4.attach(38);
  NovaServo_5.attach(40);

  NovaServo_1.write(90);
  NovaServo_2.write(90);
  NovaServo_3.write(90);
  NovaServo_4.write(90);
  NovaServo_5.write(95);

}

/**
   Maps the potentiometer
*/
void joystickCalibration() {

  value1_x = analogRead(joystick1_x);
  value1_y = analogRead(joystick1_y);
  value2_x = analogRead(joystick2_x);
  value2_y = analogRead(joystick2_y);

  value1_sw = digitalRead(joystick1_sw);
  value2_sw = digitalRead(joystick2_sw);

  value1_x = map(value1_x, 0, 1024, 170, 10);
  value1_y = map(value1_y, 0, 1024, 50, 170);
  value2_x = map(value2_x, 0, 1024, 40, 140);
  value2_y = map(value2_y, 0, 1024, 40, 160);

  value1_xF = value1_xF * (1 - filter1_x) + value1_x * filter1_x;
  value1_yF = value1_yF * (1 - filter1_y) + value1_y * filter1_y;
  value2_xF = value2_xF * (1 - filter2_x) + value2_x * filter2_x;
  value2_yF = value2_yF * (1 - filter2_y) + value2_y * filter2_y;

  // Checks whether the variable "degree" should be increased/decreased by 2 degrees at each iteration
  if (value1_sw == ACTIVATED) {
    if (degree < 141) degree = degree + 2;
  }

  if (value2_sw == ACTIVATED) {
    if (degree > 89) degree = degree - 2;
  }
  delay(30);

  if (value1_yF > 80)      NovaServo_1.write(value1_yF);
  NovaServo_2.write(value2_xF);
  if (value2_yF > 65)      NovaServo_3.write(value2_yF);
  NovaServo_4.write(value1_xF);
  NovaServo_5.write(degree);

}

/**
   Some simple movements with increments.
*/
void movement() {
  int x = 1;
  int timer = 45;
  for (int i = 50; i > 49; i = i + x) {
    NovaServo_2.write(i);
    if (i < 90) timer = timer - x;
    if (i > 90) timer = timer + x;
    if (i == 130) x = -1;      // switch direction at peak
    delay(timer);
  }
}
