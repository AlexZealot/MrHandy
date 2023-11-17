#include "Hand.h"
#include <Arduino.h>

Hand::Hand(){

}

void Hand::begin(){
  _pwmServo  = Adafruit_PWMServoDriver(0x40);
  _pwmServo.begin();
  _pwmServo.setPWMFreq(PWM_FREQ);
  
  _T = millis();  
}

int Hand::pulseWidth(int _angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(_angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * PWM_FREQ * 4096);
  return analog_value;
}

void Hand::update(unsigned long T){
  int D = T - _T;
  _T = T;

  angle[ID_TURN] += speed[ID_TURN] * (int)D / 150;
  angle[ID_TURN] = constrain(angle[ID_TURN], 0, 180);

  angle[ID_FULL_HAND] += speed[ID_FULL_HAND] * D / 150;
  angle[ID_FULL_HAND] = constrain(angle[ID_FULL_HAND], 0, 135);  

  angle[ID_UP_DOWN] += speed[ID_UP_DOWN] * D / 150;
  angle[ID_UP_DOWN] = constrain(angle[ID_UP_DOWN], 0, 90);
  
  /*коррекция ID_UP_DOWN в зависимости от ID_FULL_HAND*/
  int tmp;
  if ((angle[ID_FULL_HAND] >= 0) && (angle[ID_FULL_HAND] <= 30) && (angle[ID_UP_DOWN] >= 0) && (angle[ID_UP_DOWN] <= 60)){
    tmp = -2*angle[ID_FULL_HAND] + 60;
    if (angle[ID_UP_DOWN] < tmp) angle[ID_UP_DOWN] = tmp;
  }

  if ((angle[ID_FULL_HAND] >= 90) && (angle[ID_FULL_HAND] <= 135) && (angle[ID_UP_DOWN] >= 40) && (angle[ID_UP_DOWN] <= 90)){
    tmp = -50*angle[ID_FULL_HAND]/45 + 190;
    if (angle[ID_UP_DOWN] > tmp) angle[ID_UP_DOWN] = tmp;
  }

  _pwmServo.setPWM(3, 0, pulseWidth( angle[ID_TURN] ));  
  _pwmServo.setPWM(15, 0, pulseWidth( angle[ID_FULL_HAND] ));  
  _pwmServo.setPWM(6, 0, pulseWidth( angle[ID_UP_DOWN] ));
  _pwmServo.setPWM(8, 0, pulseWidth( angle[ID_CLAW] ));
}

void Hand::die(unsigned long T){
  _T = T;
  _pwmServo.setPWM(3, 0, 4096);  
  _pwmServo.setPWM(15, 0, 4096);  
  _pwmServo.setPWM(6, 0, 4096);
  _pwmServo.setPWM(8, 0, 4096);
}

int Hand::getAngle(int ID){
  return angle[ID];
}
