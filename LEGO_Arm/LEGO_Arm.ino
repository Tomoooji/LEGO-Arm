#if define(ARDUINO)
  #include <Servo.h>
#elif define(ESP32)
  #include <ESP32Servo.h>
#endif

const int LENGTH[] = {}; // base,upper,lower
const float GEAR = ;

float habd[2]; //{x, y}
float angleR, angleL;
int servoR_ang, servoL_ang;
servo ServoR, servoL;

void setup(){}

void loop(){}
