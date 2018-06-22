// 시리얼 통신으로 a를 날리면 모터가 테스트 구동을 하고 LED가 꺼짐, b를 날리면 모터가 멈추고 LED(13번)가 켜짐  

int enA = 3;
int in1 = 12;
int led = 13;
char incomingByte;

void setup() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    if(incomingByte == 'a') {
      digitalWrite(led, LOW);
      slowRunStop();  
    }
    if(incomingByte == 'b') {
      digitalWrite(led, HIGH);
    }
  }
}

void slowRunStop() {
  for(int i = 0; i < 256; i++) {
    digitalWrite(in1, HIGH);
    analogWrite(enA, i);
    delay(10);
  }
  
  for(int i = 255; i > 0; i--) {
    digitalWrite(in1, HIGH);
    analogWrite(enA, i);
    delay(10);
  }
  for(int i = 0; i < 256; i++) {
    digitalWrite(in1, LOW);
    analogWrite(enA, i);
    delay(10);
  }
  for(int i = 255; i > 0; i--) {
    digitalWrite(in1, LOW);
    analogWrite(enA, i);
    delay(10);
  }
}
