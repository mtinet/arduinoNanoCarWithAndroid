// command에 1000이 들어오면 모터를 구동하고, 아니면 1000이 들어올 때까지 자리를 이동  
#include <SoftwareSerial.h>
#include <Servo.h>


int enA = 3;
int in1 = 12; 
int in2 = 9; //brake
int ledRed = 13;
int ledBlue = 10;  

Servo myServo;
int command = 0;
int dir = 0;
int valServo = 90;
int valMotor = 0;

int temp1 = 0;

SoftwareSerial mySerial(6, 7);

void setup() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  
  myServo.attach(5);
  myServo.write(valServo);
  
  digitalWrite(in1, HIGH);
  analogWrite(enA, valMotor);
  
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  parse();
  servoValueMapping();
  modifyAndInput();
}       
  
// 입력신호를 각각의 값으로 분기    
void parse() {
  if(mySerial.available()) {
    if(mySerial.read() == '\n') {
      command = mySerial.parseInt();
      dir = mySerial.parseInt();
      valServo = mySerial.parseInt();
      valMotor = mySerial.parseInt();
    }
  }
}

// servoValueMapping
void servoValueMapping() {
  valServo = map(valServo, -100, 100, 30, 150);
}

// 전달되는 값의 시작을 가르쳐주는 수치 '1000'의 자리가 틀릴 경우 자릿수를 보정  
void modifyAndInput() {
  if (command != 1000) { 
      temp1 = command;
      command = dir;
      dir = valServo;
      valServo = valMotor;
      dir = temp1;   
      Serial.print("out  "); 
      Serial.print(command);
      Serial.print("  ");  
      Serial.print(dir);
      Serial.print("  ");
      Serial.print(valServo);
      Serial.print("  ");
      Serial.print(valMotor);
      Serial.println("  ");
   } else  {
      Serial.print("in   ");  
      Serial.print(command);
      Serial.print("  ");
      Serial.print(dir);
      Serial.print("  ");
      Serial.print(valServo);
      Serial.print("  ");
      Serial.println(valMotor);
          
    // forward : dir == 1, backward : dir == 2, stop : dir == 0  
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



// 전진함수  
void forwardCar(int dir, int valServo, int valMotor) {
  myServo.write(valServo);
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(in1, HIGH);
  analogWrite(enA, valMotor);
}

// 후진함수  
void backwardCar(int dir, int valServo, int valMotor) {
  myServo.write(valServo);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledRed, HIGH);
  digitalWrite(in1, LOW);
  analogWrite(enA, valMotor);
}

//정지함수  
void stopCar(int valServo) {
  myServo.write(valServo);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
}
