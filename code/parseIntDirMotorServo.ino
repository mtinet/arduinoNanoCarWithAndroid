// 시리얼을 읽은 다음 parseInt()함수를 사용해 각각의 변수에 나누어 넣은 다음 그 변수의 값에 해당하는 방향, 모터속도, 서보모터 조향값으로 입력함
// 1 == forward, 2 == backward, 0 == stop  
// 데이터 형식(ex. 1 90 255)

#include <Servo.h>

int enA = 3;
int in1 = 12; 
int in2 = 9; //brake
int ledRed = 13;
int ledBlue = 5;

int dir = 0;

Servo myServo;
int valServo = 90;
int valMotor = 0;

void setup() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(ledRed, OUTPUT);
  
  myServo.attach(5);
  myServo.write(valServo);
  
  digitalWrite(in1, HIGH);
  analogWrite(enA, valMotor);
  
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    dir = Serial.parseInt();
    valServo = Serial.parseInt();
    valMotor = Serial.parseInt();
    Serial.print(dir);
    Serial.print("  ");
    Serial.print(valServo);
    Serial.print("  ");
    Serial.println(valMotor);
    
    // dir == 1 forward, dir ==2 backward
    if (dir == 1) {
      forwardCar(dir, valServo, valMotor);
    }
    if (dir == 2) {
      backwardCar(dir, valServo, valMotor);
    }
    if (dir == 0) {
      stopCar(valServo);
    }       
  }
}

void forwardCar(int dir, int valServo, int valMotor) {
  myServo.write(valServo);
  digitalWrite(ledRed, HIGH);
  digitalWrite(in1, HIGH);
  analogWrite(enA, valMotor);
}

void backwardCar(int dir, int valServo, int valMotor) {
  myServo.write(valServo);
  digitalWrite(ledRed, HIGH);
  digitalWrite(in1, LOW);
  analogWrite(enA, valMotor);
}

void stopCar(int valServo) {
  myServo.write(valServo);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
}
  
