# arduinoNanoMotorDriver


## ArduinoNanoCar using Android phone
### 재료  
- Arduino Nano  
- Arduino Nano Motor Driver  
- Bluetooth HC-06  
- DC Motor
- Servo Motor
- App Inventor(Android Phone App Creator, Using Accelerometer, Gauge, Button)

### 프로그램  
- [Arduino Code](https://github.com/mtinet/arduinoNanoCarWithAndroid/blob/master/code/arduinoNanoCar.ino)  
- [App Inventor .aia](https://github.com/mtinet/arduinoNanoCarWithAndroid/blob/master/appInventor/accelerometerServoSteer.aia)  - [App Inventor .apk](https://github.com/mtinet/arduinoNanoCarWithAndroid/blob/master/appInventor/accelerometerServoSteer.apk)  

### 테스트 사진  
![](https://github.com/mtinet/arduinoNanoCarWithAndroid/blob/master/image/20180622_111258.jpg?raw=true)  

### 도면  


### 아두이노 나노 모터 드라이버 관련 정보  
##### Link : [arduinoNanoMotorDriver](https://www.ebay.com/itm/L298P-2A-Dual-Channel-DC-Stepper-Motor-Driver-Shield-Module-For-Arduino-Nano-3-0-/201852742335)

L298P 2A Dual Channel DC Stepper Motor Driver Shield Module For Arduino Nano 3.0  
![](https://github.com/mtinet/arduinoNanoMotorDriver/blob/master/image/2033869278.jpg?raw=true)  


The NANO Motor Shield is based on the L298P, which is a dual full-bridge driver designed to drive inductive loads such as relays, solenoids, DC and stepping motors. It lets you drive two DC motors with your Arduino NANO board, controlling the speed and direction of each one independently. You can also measure the motor current absorption of each motor, among other features.  

You can find in the Getting Started section all the information you need to configure your board, use the Arduino Software (IDE), and start tinker with coding and electronics.  


## Technical specs
Operating Voltage   5V to 12V

Motor controller    L298P, Drives 2 DC motors or 1 stepper motor

Max current         2A per channel or 4A max (with external power supply)

Current sensing     1.65V/A

Free running stop and brake function



### Power  
The NANO Motor Shield must be powered only by an external power supply. Because the L298 IC mounted on the shield has two separate power connections, one for the logic and one for the motor supply driver. The required motor current often exceeds the maximum USB current rating.  

External (non-USB) power can come either from an AC-to-DC adapter (wall-wart) or battery. The adapter can be connected by plugging a 2.1mm center-positive plug into the Arduino's board power jack on which the motor shield is mounted or by connecting the wires that lead the power supply to the Vin and GND screw terminals, taking care to respect the polarities.  

To avoid possible damage to the Arduino board on which the shield is mounted, we reccomend using an external power supply that provides a voltage between 7 and 12V. If your motor require more than 9V we recommend that you separate the power lines of the shield and the Arduino board on which the shield is mounted. This is possible by cutting the "Vin Connect" jumper placed on the back side of the shield. The absolute limit for the Vin at the screw terminals is 18V.  

The shield can supply 2 amperes per channel, for a total of 4 amperes maximum.   

### Input and Output  
This shield has two separate channels, called A and B, that each use 4 of the Arduino pins to drive or sense the motor. In total there are 8 pins in use on this shield. You can use each channel separately to drive two DC motors or combine them to drive one bipolar stepper motor. The shield's pins, divided by channel are shown in the table below:  

Function          pins per Ch. A    pins per Ch. B  
Direction         D12               D13  
PWM               D3                D11  
Brake             D9                D8  
Current Sensing   A0                A1  

If you don't need the Brake and the Current Sensing and you also need more pins for your application you can disable this features by cutting the respective jumpers on the back side of the shield.  

##### [Schematic Download](https://github.com/mtinet/arduinoNanoMotorDriver/blob/master/arduinoNanoMotorDriver.pdf)

### Motors Connection  
Brushed DC motor. You can drive two Brushed DC motors by connecting the two wires of each one in the (+) and (-) screw terminals for each channel A and B. In this way you can control its direction by setting HIGH or LOW the DIR A and DIR B pins, you can control the speed by varying the PWM A and PWM B duty cycle values. The Brake A and Brake B pins, if set HIGH, will effectively brake the DC motors rather than let them slow down by cutting the power. You can measure the current going through the DC motor by reading the SNS0 and SNS1 pins. On each channel will be a voltage proportional to the measured current, which can be read as a normal analog input, through the function analogRead() on the analog input A0 and A1. For your convenience it is calibrated to be 3.3V when the channel is delivering its maximum possible current, that is 2A. 


### Test Sketch
```
// connect motor controller pins to Arduino digital pins
// motor one
int enA = 3;
int in1 = 9;
int in2 = 12;
// motor two
int enB = 11;
int in3 = 8;
int in4 = 13;
void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
void loop()
{
  demoOne();
  delay(1000);
  demoTwo();
  delay(1000);
}
```
