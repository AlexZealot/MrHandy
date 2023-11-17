#include "BatCheck.h"
#include <Arduino.h>

BatCheck::BatCheck(int _inp_v, int _r, int _g, int _y){
  inp_v = _inp_v;
  r = _r;
  g = _g;
  y = _y;

  //pinMode(inp_v, INPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(y, OUTPUT);
  startTime = millis();
  isBlink = false;
  update(startTime); 
}

bool BatCheck::update(unsigned long T){
  float tmp = 5.0f*analogRead(inp_v)/1023.0f;
  float tmpV;

  tmpV = tmp*2.03f;
  if (abs(tmpV - V) < 0.1f )
    V += (tmpV - V) * FILTER_KOEF;
  else 
    V += (tmpV - V) * FILTER_KOEF_B;

  /*настройка мигалки*/
  bool  HIGH_STATE = isBlink?(((T - startTime)/BLINK_INTERVAL)%2 == 0):HIGH;

  /*Петля гестерезиса*/
  /*  переход и BAT_OK в BAT_WARN*/
  if (batState == BAT_OK && V < 7.65f) batState = BAT_WARN;
  /*  переход из BAT_WARN в BAT_OK*/
  if (batState == BAT_WARN && V > 7.95f) batState = BAT_OK;
  /*  переход из BAT_WARN в BAT_DISCH*/
  if (batState == BAT_WARN && V < 7.25f) batState = BAT_DISCH;
  /*  переход из BAT_DISCH в BAT_WARN*/
  if (batState == BAT_DISCH && V > 7.55f) batState = BAT_WARN;

  if (batState == BAT_OK) {
    digitalWrite(g, HIGH_STATE);
    digitalWrite(r, LOW);
    digitalWrite(y, LOW);
    return true;
  } else
  if (batState == BAT_WARN) {
    digitalWrite(y, HIGH_STATE);
    digitalWrite(r, LOW);
    digitalWrite(g, LOW);
    return true;
  } else {
    digitalWrite(r, HIGH_STATE);
    digitalWrite(y, LOW);
    digitalWrite(g, LOW);
    return false;
  }
}
