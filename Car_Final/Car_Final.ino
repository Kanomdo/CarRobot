
//----------------------------------------------------- Initialization
#define trig A0
#define echo A1
// กำหนดค่าเกณฑ์กำหนดว่าระยะทางเท่าไหร่ sensor ถึงจะ dectect (หน่วยเป็นเซนติเมตร)
int thresholddistance = 30;

//สามารถกำหนดขอบเขตของมุม เช่น 0-60 เป็นมุมทางด้านขวา, 120-180 เป็นมุมทางด้านซ้าย และที่เหลือจะมุมของตรงกลาง
int angleRight = 60;
int angleLeft = 120;

long duration;
float forwarddistance;
float distancefront;
float distanceArr[181];

#define LeftSensor A2
#define RightSensor A4
#define FontSensor A5
#define Backsensor A3

#include <Servo.h>
#define pinServo 2
int pos = 0;
//----------------------------------------------------- Initialization: Setting up Servo Angles
int servoArray[181];
Servo myServo;
//----------------------------------------------------- Initialization: Motors
int motor_left[] = {10, 9, 8};
int motor_right[] = {5, 7, 6};
//----------------------------------------------------- Initialization: Setup Module
void setup()
{
  Serial.begin(9600);
  myServo.attach(pinServo);
  // Setup Motors
  for (int i = 0; i < 3; i++)
  {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  // Setup Sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  pinMode(FontSensor, INPUT);
  pinMode(Backsensor, INPUT);
}
//----------------------------------------------------- Initialization: Motor Module

// Following Module is for the Robot to enable motor
void enableMotor()
{
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_right[0], HIGH);
}

// Following Module is for the Robot to disable motor
void disableMotor()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_right[0], LOW);
}

// Following Module is for the Robot to brake
void brake()
{
  disableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], LOW);
}

// Following Module is for the Robot to go forward
void drive_forward()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  delayMicroseconds(400);
  digitalWrite(motor_left[2], HIGH);
  delayMicroseconds(1000 - 400);
  digitalWrite(motor_right[1], LOW);
  delayMicroseconds(1000 - 400);
  digitalWrite(motor_right[2], HIGH);
  delayMicroseconds(400);
}

// Following Module is for the Robot to go backward
void drive_backward()
{
  enableMotor();
  digitalWrite(motor_left[1], HIGH);
  delayMicroseconds(400);
  digitalWrite(motor_left[2], LOW);
  delayMicroseconds(1000 - 400);
  digitalWrite(motor_right[1], HIGH);
  delayMicroseconds(1000 - 400);
  digitalWrite(motor_right[2], LOW);
  delayMicroseconds(400);
}

// Following Module is for the Robot to slightly go towards left
void slight_left()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], HIGH);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], LOW);
  delay(600);
}

// Following Module is for the Robot to slightly go towards right
void slight_right()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], HIGH);
  delay(600);
}

// Following Module is for the Robot to turn left
void turn_right()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], HIGH);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], LOW);
  delay(900);
}
// Following Module is for the Robot to turn right
void turn_left()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], HIGH);
  delay(900);
}

// Following Module is to make a uturn if there are obstacles to the right, to the left and in front
void turn_around()
{
  enableMotor();
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], HIGH);
  digitalWrite(motor_right[2], LOW);
  delay(600);
}

// Following recored distance in each angle
void commitValue(int pos)
{
  myServo.write(pos);
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distanceArr[pos] = duration / 58;
  Serial.print("distanceArr[");
  Serial.print(pos);
  Serial.print("] = ");
  Serial.println(distanceArr[pos]);
}

// ตรวจจับและทำตามคำสั่ง
void detected(int pos)
{
  if (digitalRead(FontSensor) == 0)
  {
    drive_backward();
    delay(1000);
    turn_around();
    delay(200);
    Serial.println("Font Dectected");
  }
  else if (digitalRead(RightSensor) == 0)
  {
    Serial.println("Right Dectected");
    turn_left();
    delay(100);
    drive_forward();
  }
  else if (digitalRead(LeftSensor) == 0)
  {
    Serial.println("Left Dectected Sensor");
    turn_right();
    delay(100);
    drive_forward();
  }
  else if (digitalRead(Backsensor) == 0)
  {
    Serial.println("Backsensor Dectected Sensor");
    drive_forward();
    delay(100);
  }
  else if (distanceArr[pos] < thresholddistance)
  {
    if (pos <= angleRight)
    {
      Serial.println("Right Dectected");
      turn_left();
      delay(100);
      drive_forward();
    }
    else if (pos >= angleLeft)
    {
      Serial.println("Left Dectected");
      turn_right();
      delay(100);
      drive_forward();
    }
    else
    {
      Serial.println("Font Dectected");
      drive_backward();
      delay(1000);
      turn_around();
      delay(200);
    }
  }
  else
  {
    drive_forward();
  }
}

// ฟังก์ชันหมุนรอบๆ 180 องศา และส่งมุมไปคำนวณระยะทาง
void scanner()
{
  for (pos = 0; pos <= 180; pos += 3)
  {
    commitValue(pos);
    detected(pos);
    delay(1);
  }
  for (pos = 180; pos >= 0; pos -= 3)
  {
    commitValue(pos);
    detected(pos);
    delay(1);
  }
}

//----------------------------------------------------- Loop Module

void loop()
{
  scanner();
}
