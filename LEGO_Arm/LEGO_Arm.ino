#include <Servo.h>

const int LENGTH[] = {2,13,15}; // base,upper,lower
const float GEAR = 3/2*RAD_TO_DEG;

float hand[2]; //{x, y}
float angleR, angleL;
int servoR_ang, servoL_ang;
servo ServoR, ServoL;

const int CENTER_X = 512, CENTER_Y = 512;
const speed_coeff; //12bit to hand potition move

// control from arduino uno shield
const int PIN_JSTK_X = A0;
const int PIN_JSTK_Y = A1;
const int PIN_SERVO_X = 11;
const int PIN_SERVO_Y = 10;
//const int PIN_BUTTON = 4;

void calcAng(){
  
}

void setup(){}

void loop(){}

