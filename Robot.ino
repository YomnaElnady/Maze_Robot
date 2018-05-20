// this code is to control maze robot with servo and DC motors for any arbitrary Maze..
#include<NewPing.h>
#include<Servo.h>
Servo s ;
int d , speed , distanceL , distanceR , motorR1 = 6 , motorR2 = 7 , motorL1 = 8 , motorL2 = 9 , enableR = 11 , enableL = 5 , TRIG = 4 , ECHO = 2 , servo = 3 ;
NewPing u(4, 2, 1000) ;
int ultrasonic ()//to get the distance .
{
  d = u.ping_cm();//read the distance in cm .
  Serial.println(d);
  return d ;
}
void forward ()
{
  digitalWrite (motorR1, HIGH);
  digitalWrite (motorR2, LOW);
  digitalWrite (motorL1, HIGH);
  digitalWrite (motorL2, LOW);
}
void turnleft ()
{
  digitalWrite (motorR1, HIGH);
  digitalWrite (motorR2, LOW);
  digitalWrite (motorL1, LOW);
  digitalWrite (motorL2, HIGH);

}
void turnright ()
{
  digitalWrite (motorR1, LOW);
  digitalWrite (motorR2, HIGH);
  digitalWrite (motorL1, HIGH);
  digitalWrite (motorL2, LOW);

}
void turnback ()
{
  digitalWrite (motorR1, HIGH);
  digitalWrite (motorR2, LOW);
  digitalWrite (motorL1, LOW);
  digitalWrite (motorL2, HIGH);
  delay(1000);
  digitalWrite (motorR1, LOW);
  digitalWrite (motorR2, LOW);
  digitalWrite (motorL1, LOW);
  digitalWrite (motorL2, LOW);
  delay(500);
}
void stopmotors ()
{
  digitalWrite (motorR1, LOW);
  digitalWrite (motorR2, LOW);
  digitalWrite (motorL1, LOW);
  digitalWrite (motorL2, LOW);
}
void back()
{

  digitalWrite (motorR1, LOW);
  digitalWrite (motorR2, HIGH);
  digitalWrite (motorL1, LOW);
  digitalWrite (motorL2, HIGH);

}
void setup() {
  pinMode (motorR1, OUTPUT); //MOTOR_R
  pinMode (motorR2, OUTPUT); //MOTOR_R
  pinMode (motorL1, OUTPUT); //MOTOR_L
  pinMode (motorL2, OUTPUT); //MOTOR_L
  pinMode (TRIG, OUTPUT); //TRIG
  pinMode (ECHO, INPUT); //ECHO
  pinMode (enableR, OUTPUT); //ENABLE
  pinMode (enableL, OUTPUT); //ENABLE
  s.attach(servo);//SERVO
  Serial.begin(9600);
}

void loop() {
  speed = 70;
  analogWrite(3, speed  );
  analogWrite(11, 85);
  s.write(90);
  ultrasonic();
  delay(100);
  if ( ultrasonic() > 7 || ultrasonic() == 0 )
  {
    forward();
  }
  else
  {
    delay(300);
    stopmotors();
    delay(1000);
    s.write(180);
    delay(500);
    distanceL = ultrasonic();
    delay(100);
    if ( distanceL > 7 || distanceL == 0 )
    {
      turnleft();
      delay (400);
      stopmotors();
      delay(500);
      s.write(90);
      forward();
    }
    else
    {
      s.write(0);
      delay(500);
      distanceR = ultrasonic();
      delay (100);
      if ( distanceR > 7 || distanceR == 0  )
      {

        turnright();
        delay (400);
        stopmotors();
        delay(500);
        s.write(90);
        forward();
      }
      else
      {

        turnback();
        s.write(90);
        forward();
      }
    }
  }
}

