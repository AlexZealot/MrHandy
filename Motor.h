#ifndef __MOTOR__
#define __MOTOR__
#include <Arduino.h>

#define BLINK_INTERVAL  250
#define MOT_BREAK       0
#define MOT_RUN         1

class SingleMotor {
  private:
    int   pinA, pinB;
    int   speed;
    byte  mode;
  public:
    SingleMotor();
    void update();
    void setSpeed(int _sp){
      speed = _sp;
    }
    void setMode(byte _mode){
      mode = _mode;
    }
    void bindPins(int _A, int _B){
      pinA = _A;
      pinB = _B;
      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
    }
    void die(){
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
    }
};

class Motor {
  private:
    SingleMotor mLeft, mRight;
  public:
    Motor(int _fl, int _bl, int _fr, int _br);

    void begin();
    void update();
    void setSpeed(int L, int R);
    void die(){
      mLeft.die();
      mRight.die();
    }
};

#endif //__MOTOR__
