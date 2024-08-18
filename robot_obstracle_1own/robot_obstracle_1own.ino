// Code for obstacle avoiding robot with ultrasonic sensor:
#include<Servo.h>
#include<AFMotor.h>
int trig=A0;
int echo=A1;
long duration;
float distance;
int d;
int Ldis;
int Rdis;
int left;
int right;
Servo s;
AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);
void setup() {
pinMode(echo,INPUT);
pinMode(trig,OUTPUT);
m1.setSpeed(200);
m2.setSpeed(200);
m3.setSpeed(255);
m4.setSpeed(255);
s.attach(10);
 start();
}
void forward()
{
m1.run(FORWARD);
m2.run(FORWARD);
m3.run(FORWARD);
m4.run(FORWARD);
}
void backward()
{
m1.run(BACKWARD);
m2.run(BACKWARD);
m3.run(BACKWARD);
m4.run(BACKWARD);
   
}
void moveright()
{
m1.run(FORWARD);
m2.run(FORWARD);
m3.run(BACKWARD);
m4.run(BACKWARD);
}
void moveleft()
{
m1.run(BACKWARD);
m2.run(BACKWARD);
m3.run(FORWARD);
m4.run(FORWARD);
}


int seeright()
{
  s.write(0);
  delay(500);
  right=ultrasonic();
  return right;
}
int seeleft()
{
  s.write(180);
  delay(500);
  left=ultrasonic();
  return left;
}


void start()
{  
  s.write(90);
  delay(3000);
}
void Stop()
{
m1.run(RELEASE);
m2.run(RELEASE);
m3.run(RELEASE);
m4.run(RELEASE);


}


int ultrasonic()
{
  digitalWrite(trig,LOW);
  delay(2);
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=(duration/2)/29.1;
  return distance;
}


void loop()
{
  d = ultrasonic();
  if (d <= 30) {
    Stop();
    backward();
    delay(100);
    Stop();
    Ldis = seeleft();
    s.write(90);
    Rdis = seeright();
    s.write(90);
    if (Ldis < Rdis) {
      moveleft();
      delay(300);
      Stop();
      delay(500);
    }
     else if (Ldis > Rdis)
      {
      moveright();
      delay(300);
      Stop();
      delay(1000);
    }
  }
  else
  {
    forward();
  }
}




