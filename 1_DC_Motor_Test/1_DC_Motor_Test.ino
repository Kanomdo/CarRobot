
//กำหนด Pin ของมอเตอร์
int motor_left[] = {10, 9, 8};
int motor_right[] = {5, 7, 6};

void setup()
{
  Serial.begin(9600);
  // Setup Pin Motors
  for (int i = 0; i < 3; i++)
  {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}

// เปิดการใช้งานมอเตอร์
void enableMotor()
{
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_right[0], HIGH);
}

// ปิดการใช้งานมอเตอร์
void disableMotor()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_right[0], LOW);
}

// ฟังก์ชันเบรกรถ
void brake()
{
  disableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], LOW);
}

// ฟังก์ชันเคลื่อนที่ไปข้างหน้า
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

// ฟังก์ชันเคลื่อนที่ไปข้างหลัง
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

// ฟังก์ชั่นเบี่ยงไปทางซ้าย
void slight_left()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], HIGH);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], LOW);
  delay(600);
}

// ฟังก์ชั่นเบี่ยงไปทางขวา
void slight_right()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], HIGH);
  delay(600);
}

// ฟังก์ชันเลี้ยวขวา
void turn_right()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], HIGH);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], LOW);
  delay(900);
}

// ฟังก์ชันเลี้ยวซ้าย
void turn_left()
{
  enableMotor();
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], HIGH);
  delay(900);
}

// ฟังก์ชันกลับรถ
void turn_around()
{
  enableMotor();
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_right[1], HIGH);
  digitalWrite(motor_right[2], LOW);
  delay(600);
}
void loop()
{
  // ฟังก์ชันบังคับรถตามใจต้องการ
  turn_right();
}
