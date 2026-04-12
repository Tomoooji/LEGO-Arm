#include <Servo.h>
//#include <ESP32Servo.h>

const int LENGTH[] = {2,13,15}; // base,upper,lower
const int LENGTH_sq[] = {sq(LENGTH[1]), sq(LENGTH[2])};
const float GEAR = 3/2*RAD_TO_DEG;

float handX, handY;
float angleR, angleL;
int servoR_ang, servoL_ang;
servo ServoR, ServoL;

const int CENTER_X = 512, CENTER_Y = 512;
const int IGNORE = 20;
const float speed_coeff = 0.01; //12bit to hand potition

// control from arduino uno shield
const int PIN_JSTK_X = A0;
const int PIN_JSTK_Y = A1;
const int PIN_SERVO_X = 11;
const int PIN_SERVO_Y = 10;

float clip2pi(float ang){
  return ang>TWO_PI? ang-TWO_PI: (ang<0? ang+TWO_PI: ang);
}

void setup(){
  pinMode(PIN_JSTK_X, INPUT);
  pinMode(PIN_JSTK_Y, INPUT);
  ServoL.attach(PIN_SERVO_L);
  ServoR.attach(PIN_SERVO_R);
}

void loop(){
  int input_x = analogRead(PIN_JSTK_X);
  int input_y = analogRead(PIN_JSTK_Y);

  handX += (abs(input_x - CENTER_X) > IGNORE)? input_x * speed: 0;
  handY += (abs(input_y - CENTER_Y) > IGNORE)? input_y * speed: 0;

  int dist_sq = sq(handX) + sq(handY);
  float dist = sqrt(dist_sq);
  float ang1 = clip2pi(atan2(handY, handX));
  float ang2 = clip2pi(acos((dist_sq + LENGTH_sq[0] - LENGTH_sq[1]) / (2 * sqrt(dist_sq) * LENGTH[1]))));

  servoR_ang = constrain((ang2 - ang1) * GEAR, 0, 180);
  servoL_ang = constrain((ang2 + ang1) * GEAR, 0, 180);

  ServoL.write(servoL_ang);
  ServoR.write(servoR_ang);
}
