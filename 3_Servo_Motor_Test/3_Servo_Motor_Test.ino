
#include <Servo.h>

// กำหนด Pin Servo
#define pinServo 2


//สามารถเปลี่ยนมุมตรงนี้ได้ให้ว่าจะใ้ห้ servo มึมไปมุมไหน
int angle = 75;


// กำหนดให้มุมเริ่มต้นของ servo เป็น 0
int pos = 0;
Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(pinServo);
}

//ฟัังก์ชัน scan 180 องศา
void scanner() {
  for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);
    Serial.println(pos);// tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);
    Serial.println(pos);// tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
}


void loop() {
  // ปรับมุม servo ไปตามมุมที่เรากำหนดไว้ด้านบน
  myServo.write(angle);

  // ถ้าอยากให้ scan 180 องศาscan 180 องศา เปิิิิดการใช้อันนี้
  //  scanner();



}
