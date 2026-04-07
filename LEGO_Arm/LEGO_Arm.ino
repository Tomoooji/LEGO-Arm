#include <Servo.h>
//#include <ESP32Servo.h>

const int LENGTH[] = {2,13,15}; // base,upper,lower
const int LENGTH_sq[] = {sq(LENGTH[1]), sq(LENGTH[2])};
const float GEAR = 3/2*RAD_TO_DEG;

float hand[2]; //{x, y}
float angleR, angleL;
int servoR_ang, servoL_ang;
servo ServoR, ServoL;

const int CENTER_X = 512, CENTER_Y = 512;
const int IGNORE = 20;
const float speed = 0.01; //12bit to hand potition

// control from arduino uno shield
const int PIN_JSTK_X = A0;
const int PIN_JSTK_Y = A1;
const int PIN_SERVO_X = 11;
const int PIN_SERVO_Y = 10;
//const int PIN_BUTTON = 4;

float clip2pi(float ang){
  return ang>TWO_PI? ang-TWO_PI: (ang<0? ang+TWO_PI: ang);
}

float calcAng(int targetX, int targetY){
  int dist_sq = sq(targetX) + sq(targetY);
  float dist = sqrt(dist_sq);
  return clip2pi(atan2(targetY, targetX) + acos((dist_sq + LENGTH_sq[0] - LENGTH_sq[1]) / (2 * dist * LENGTH[1])));
}

void setup(){
  //Serial.begin(9600);
  //pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_JSTK_X, INPUT);
  pinMode(PIN_JSTK_Y, INPUT);
  ServoL.attach(PIN_SERVO_L);
  ServoR.attach(PIN_SERVO_R);
}

void loop(){
  //if(digitalRead(PIN_BUTTON)){
  int input_x = analogRead(PIN_JSTK_X);
  int input_y = analogRead(PIN_JSTK_Y);
  hand[0] += (abs(input_x - CENTER_X) > IGNORE)? input_x * speed: 0;
  hand[1] += (abs(input_y - CENTER_Y) > IGNORE)? input_y * speed: 0;
  servoL_ang = constrain(calcAng(hand[0] - LENGTH[0], hand[1]) * GEAR, 0, 180);
  servoR_ang = constrain(calcAng(hand[0] + LENGTH[0], hand[1]) * GEAR, 0, 180);
  ServoL.write(servoL_ang);
  ServoR.write(servoR_ang);
  //}
  //else{
    //Serial.print(CENTER_X = analogRead(PIN_JSTK_X));
    //Serial.pribt(",");
    //Serial.print(CENTER_Y = analogRead(PIN_JSTK_Y));
}
