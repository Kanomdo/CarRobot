

// กำหนด Pin ของ Ultrasonic
#define trig A0
#define echo A1

// กำหนดตัวแปร
long duration, distance;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop()
{

  // ปล่อยสัญญาณ pulse
  digitalWrite(trig, HIGH);

  // 10 ไมโครวินาที
  delayMicroseconds(10);

  // ปิดการปล่อยสัญญาญ pulse
  digitalWrite(trig, LOW);

  // เปิดช่องรับสัญญาญ
  duration = pulseIn(echo, HIGH);

  // คำนวณระยะทาง
  distance = duration / 58;

  // หน่วงเวลา 100 มิลลิวินาที
  delay(100);

  // แสดงผลระยะทาง
  Serial.print("Distance: ");
  Serial.println(distance);
}
