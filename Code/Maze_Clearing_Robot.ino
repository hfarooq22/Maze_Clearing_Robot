#include <NewPing.h> //Ultrasonic sensor function library
#include <Servo.h> // Servo motor library

//Ultrasonic sensor pins
#define trig_pin A0
#define echo_pin A1

//L298N pins 
const int RMF = 3;
const int RMB = 4;
const int LMF = 5;
const int LMB = 6;

//other
#define max_distance 200
NewPing sensor(trig_pin,echo_pin,max_distance);
Servo servo_motor;
boolean goesForward = false;
int distance = 0;


void setup() 
{
  //setting motors as output devices
  pinMode(RMF, OUTPUT);
  pinMode(RMB, OUTPUT);
  pinMode(LMF, OUTPUT);
  pinMode(LMB, OUTPUT);
  
  servo_motor.attach(11); //servo pin
  servo_motor.write(115);

  //calibration
  delay(2000);
  distance = pingRead();
  delay(100);
  distance = pingRead();
  delay(100);
  distance = pingRead();
  delay(100);
  distance = pingRead();
  delay(100);
}

void loop() 
{
  int rightDistance = 0;
  int leftDistance = 0;
  delay(100);

  if (distance <= 20)
  {
    stopMoving();
    delay(300);
    goBackward();
    delay(400);
    stopMoving();
    delay(300);
    leftDistance = checkLeft();
    delay(300);
    rightDistance = checkRight();
    delay(300);

    if (distance >= rightDistance)
    {
      turnLeft();
      stopMoving();
    }
    else
    {
      turnRight();
      stopMoving();
    }
  }
  else
  {
    goForward(); 
  }
    distance = pingRead();
}

int pingRead()
{
  delay(70);
  int cm = sensor.ping_cm();
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void stopMoving()
{
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, LOW);
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, LOW);
}

void goForward()
{
  if(!goesForward)
  {
    goesForward=true;
    digitalWrite(RMF, HIGH);
    digitalWrite(LMF, HIGH);
    digitalWrite(RMB, LOW);
    digitalWrite(LMB, LOW);
  }
}

void goBackward()
{
  goesForward=false;
  digitalWrite(RMB, HIGH);
  digitalWrite(LMB, HIGH);
  digitalWrite(RMF, LOW);
  digitalWrite(LMF, LOW);
}

void turnRight()
{
  digitalWrite(RMB, HIGH);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, LOW);
  digitalWrite(LMB, LOW);
  delay(500);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMB, LOW);
  digitalWrite(LMB, LOW);
}

void turnLeft()
{
  digitalWrite(RMF, HIGH);
  digitalWrite(LMB, HIGH);
  digitalWrite(RMB, LOW);
  digitalWrite(LMF, LOW);
  delay(500);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMB, LOW);
  digitalWrite(LMB, LOW);
}

int checkRight()
{  
  servo_motor.write(50);
  delay(500);
  int distance = pingRead();
  delay(150);
  servo_motor.write(115);
  return distance;
}

int checkLeft()
{
  servo_motor.write(180);
  delay(500);
  int distance = pingRead();
  delay(150);
  servo_motor.write(115);
  return distance;
  delay(150);
}
