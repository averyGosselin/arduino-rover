/*
 * Author: Avery Gosselin
 * Last Updated: 9/27/2021
*/
#include <Servo.h>

//Servo
Servo servo;
int curPos = 90;

//Joystick
int VRx = A1;
int VRy = A2;
int xPosition = 0;
int yPosition = 0;
int mapX = 0;
int mapY = 0;

void setup()
{
  //Initialize motor 
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13, HIGH);

  //Initialize servo
  servo.attach(3);
  servo.write(90);

  //Initialize joystick
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  
  //Uncomment this for serial monitor debugging
  //Serial.begin(9600);
}

/*
* Turns the front wheels to a target angle at a slow (1), medium (2), or high (3) speed
* target: the angle the servo should be set to to turn the wheels 
* speed: the speed at which the servo will be set to target, allowed speeds:
*   slow = 1
*   medium = 2
*   fast = 3
*/
void turn(int target, int speed = 2)
{
  int toAdd = 0;
  
  //Find out if the servo angle needs to increase or decrease
  if(target > curPos){
    toAdd = 1;
  }
  else{
    toAdd = -1;
  }

  //Turns the servo at the designated speed, defaults to medium if not specified or a valid number
  if(speed == 1){
    while(curPos != target){
      curPos += toAdd;
      delay(20);
      servo.write(curPos);
    }
  }
  else if(speed == 3){
    while(curPos != target){
      curPos += toAdd;
      delay(5);
      servo.write(curPos);
    }
  }
  else {
    while(curPos != target){
      curPos += toAdd;
      delay(5);
      servo.write(curPos);
    }
  }
}

//Drive the rover backwards (may vary depending on how you wired the motor)
void backward()
{
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(9, HIGH);
}

//Drive the rover forwards (may vary depending on how you wired the motor)
void forward()
{
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(9, LOW);
}

//Stops the rover
void halt()
{
  digitalWrite(13, LOW);
}


void loop()
{
  //Find out where the joystick is
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  //If joystick pressed forward/backward move in desired direction, or stop
  if (mapX < -50){
    forward();
  }
  else if(mapX > 50){
    backward();
  }
  else {
    halt();
  }

  //If joystick turned left/right turn wheels to a set left/right angle
  //TODO: make the turning more dynamic so pushing farther in a direction makes it turn harder
  if(mapY > 25){
    turn(60);
  }
  else if(mapY < -25){
    turn(120);
  }
  else{
    turn(90);
  }
}
