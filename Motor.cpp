#include "Motor.h"
#include <Arduino.h>

SingleMotor::SingleMotor(){
  speed = 0;
  mode = MOT_BREAK;
}

void SingleMotor::update(){
  if (speed == 0){
    digitalWrite(pinA, (mode == MOT_BREAK)?1:0);
    digitalWrite(pinB, (mode == MOT_BREAK)?1:0);
  }
  if (speed > 0){
    analogWrite(pinA, constrain(speed, 0, 255));
    digitalWrite(pinB, 0);
  }
  if (speed < 0){
    analogWrite(pinA, 255+constrain(speed, -255, 0));
    digitalWrite(pinB, 1);
  }
}

Motor::Motor(int _fl, int _bl, int _fr, int _br){
  mLeft.bindPins(_fl, _bl);
  mRight.bindPins(_fr, _br);
}

void Motor::begin(){
  setSpeed(0,0);
}

void Motor::update(){
  mLeft.update(); 
  mRight.update();
}

void Motor::setSpeed(int L, int R){
  mLeft.setSpeed(L); 
  mRight.setSpeed(R);
}
