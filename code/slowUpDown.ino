int enA = 3;
int in1 = 12;

void setup() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
}

void loop() {
  slowRunStop();
}

//천천히 속도가 올라갔다가 내려가는 것을 반복  
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
