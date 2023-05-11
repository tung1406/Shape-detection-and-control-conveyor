#include <Servo.h> //Declare the servo library and define the connection pins
#define IN1 4
#define IN2 3
#define IN3 6
#define IN4 5
#define sensor 2
Servo s1;
Servo s2;
Servo s3;

/////////////////////////////////////////////Servo////////////////////////////////////////////////
void servo1() // Set the first servo motor to rotate 45 degrees in t=4.25s
{
  s1.write(135);
  delay(4250);
  s1.write(180);
}

void servo2() // Set the second servo motor to rotate 45 degrees in t=4.25s
{
  s2.write(45);
  delay(4250);
  s2.write(0);
}
////////////////////////////////////////Conveyor////////////////////////////////////////////////
void Conveyor_on() //Turn on the conveyor motor
{
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 180);
}
void Conveyor_off() //Turn off the conveyor motor
{
  digitalWrite(IN1, LOW);
  analogWrite(IN2, LOW);
}
void setup() 
{
  pinMode(IN1, OUTPUT); // Setup the pins
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(sensor, INPUT);
  s1.attach(9);
  s2.attach(10);
  s3.attach(11);
  
  s1.write(180);  // Set the default angle of the servo motors
  delay(15);
  s2.write(0);
  Serial.begin(9600);
}
/////////////////// LOOP////////////////////////////////////
void loop()
{
  // Check for objects
  int sensorState = digitalRead(sensor);  //Read the sensor
  if (sensorState == 1) // If there's no object, run the conveyor
  {
    Conveyor_on();
  }
  else              // If there's no object, run the conveyor
  { 
    delay(550);
    Conveyor_off();
    delay(3000);
    Conveyor_on();
    delay(4750);
    // Receive data from RASPBERRY 
    if (Serial.available() > 0) {
      String shape = Serial.readStringUntil('\n');
      // Compare data
      if ( shape =="rectangle" ) 
      {
          servo1();
      }
      if (shape =="triangle" ) 
      {
          servo2();
      }

    }

  }
}
