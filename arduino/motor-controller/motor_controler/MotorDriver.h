#ifndef MotorDriver_H
#define MotorDriver_H
#include "Arduino.h"

class MotorDriver {
private:

  int fwdPin;
  int revPin;
  int spdPin;

  int spd = 0;
  bool forward = true;

public:
  MotorDriver(int fPin, int rPin, int pwmPin);

  void init();

  //speed 0-1000
  void setSpeed(int speed);

  void setDirection(bool fwd);
  String getState();
};

#endif
