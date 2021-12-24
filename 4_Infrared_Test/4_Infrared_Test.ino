#define LeftSensor A2
#define RightSensor A4
#define FontSensor A5
#define Backsensor A3

void setup() {
  Serial.begin(9600);
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  pinMode(FontSensor, INPUT);
  pinMode(Backsensor, INPUT);

}

void loop() {
  
  if (digitalRead(FontSensor) == 0) {
    Serial.println("Font Dectected");
  }
  else if (digitalRead(RightSensor) == 0) {
    Serial.println("Right Dectected");
  }
  else if(digitalRead(LeftSensor) ==0){
    Serial.println("Left Dectected Sensor");
  }
  else if(digitalRead(Backsensor) ==0){
    Serial.println("Backsensor Dectected Sensor");
  }
  else{
    Serial.println("Not Dectect");
  }
}
