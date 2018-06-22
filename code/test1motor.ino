// 모터 한 개 제어  
int enA = 3;
int in1 = 12;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  delay(3000);

  digitalWrite(in1, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  delay(3000);
}

void loop()
{
  demoOne();
}
