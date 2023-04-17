
#include <Stepper.h>
#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
//sensor pins
#define maximum_distance 200
#define trig_pin A3 //analog input 1
#define echo_pin A2 //analog input 2
//Steps
const int stepsPerRevolution = 2048;
const int stepsPerRevolution1 = 2048;
Stepper stepper1 = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper stepper2 = Stepper(stepsPerRevolution, 4, 6, 5, 7);
boolean goesForward = false;

int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; 


void setup(){
  //set the motor 1
Serial.begin(9600);

  servo_motor.attach(12); //our servo pin

  servo_motor.write(110);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(70);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(110);
  return distance;
}

int lookLeft(){
  servo_motor.write(150);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(110);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
 Serial.println("counterclockwise");
//
servo_motor.write(110);
//Set Stepper speeds
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  //
  //Run steppers
  stepper1.step(stepsPerRevolution/2000);
  stepper2.step(stepsPerRevolution1/2000);
}

void moveForward(){

  Serial.println("clockwise");
//
servo_motor.write(110);
//Set Stepper speeds
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  //
  //Run steppers
  stepper1.step(stepsPerRevolution/400);
  stepper2.step(stepsPerRevolution1/400);
}

void moveBackward(){
  Serial.println("counterclockwise");
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  //
  //Run steppers
  servo_motor.write(110);
  stepper1.step(stepsPerRevolution/400);
  stepper2.step(stepsPerRevolution1/400);
}

void turnRight(){
  Serial.println("clockwise");
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  //
  //Run steppers
  stepper2.step(stepsPerRevolution1);
  stepper1.step(stepsPerRevolution/200);
}

void turnLeft(){
  servo_motor.write(110);
  Serial.println("clockwise");
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  //
  //Run steppers
  stepper1.step(stepsPerRevolution);
  stepper2.step(stepsPerRevolution1/200);
}