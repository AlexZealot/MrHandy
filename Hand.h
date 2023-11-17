#ifndef __HAND__
#define __HAND__

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//поворот вправо-влево 0-180
//наклон всей руки 0-135
//вторая серва 0-90
//клешня 176-145

#define ID_CLAW         3
#define ID_UP_DOWN      2
#define ID_FULL_HAND    1
#define ID_TURN         0

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define PWM_FREQ              50

class Hand {
  private:
    Adafruit_PWMServoDriver   _pwmServo;

    int pulseWidth(int _angle);
    unsigned long _T;

    int angle[4] = {90,30,15,176};
    int speed[4] = {0,0,0,0};
  public:
    Hand();
    void  begin();
    int getAngle(int ID);    

    void CloseClaw(){
      angle[ID_CLAW] = 176;
    }

    void OpenClaw(){
      angle[ID_CLAW] = 145;
    }

    bool ClawOpened(){
      return angle[ID_CLAW] == 145;
    }

    void setSpeed(int ID, int _speed){
      speed[ID] = _speed;
    }

    void setAngle(int ID, int _angle){
      angle[ID] = _angle;
    }

    void setDefaults(){
      angle[0] = 90;
      angle[1] = 30;
      angle[2] = 15;
      angle[3] = 176;
    }

    void update(unsigned long T);
    void die(unsigned long T);
};

#endif //__HAND__
