#include <PID_v1.h>
#include <Servo.h>

Servo NovaServo_1; //Head Movement - Front and Back
Servo NovaServo_2; //Head Rotation - Clockwise and Anticlockwise
Servo NovaServo_3; //Head Rotation - Up and Down
Servo NovaServo_4; //Whole Body Rotation - Z axis
Servo NovaServo_5; //Head Movement - Up and Down

const int trigPin = 46;
const int echoPin = 44;

long duration;
int distance;
int servoAngle = 110;

double Setpoint, Input, Output; ​

double Kp = 0.51;
double Ki = 1.1;
double Kd = 0;

PID PID1(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  NovaServo_1.attach(32);
  NovaServo_1.write(servoAngle);

  PID1.SetMode(AUTOMATIC);
  PID1.SetSampleTime(10);
  PID1.SetOutputLimits(-3, 3);

  Setpoint = 15;
  Input = distance;

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Input = distance;

  PID1.Compute();

  if (distance < 30 && distance > 9) {
    servoAngle = servoAngle - Output;
    if (servoAngle < 150 && servoAngle > 80) {
      NovaServo_1.write(servoAngle);
    }
  }
}
