#include "Arduino.h"
#include "pins_arduino.h"
#include "MotorDriver.h"
#include <pins_arduino.h>
#include <stdlib.h>

MotorDriver::MotorDriver(int fPin, int rPin, int pwmPin) {
  this->fwdPin = fPin;
  this->revPin = rPin;
  this->spdPin = pwmPin;
  this->spd = 0;
  this->forward = true;
}

void MotorDriver::init() {
  pinMode(this->fwdPin, OUTPUT);  // 0x1 = output
  pinMode(this->revPin, OUTPUT);
  pinMode(this->spdPin, OUTPUT);
}


//speed 0-100
void MotorDriver::setSpeed(int speed) {
  this->spd = speed;
  int pwmOutput = map(speed, 0, 100, 0, 255);  // Map the spd value from 0 to 255
  analogWrite(this->spdPin, pwmOutput);         // Send PWM signal to L298N Enable pin
};

void MotorDriver::setDirection(bool fwd) {
  this->forward = fwd;
  if (fwd) {
    digitalWrite(this->fwdPin, HIGH);
    digitalWrite(this->revPin, LOW);
  } else {
    digitalWrite(this->fwdPin, LOW);
    digitalWrite(this->revPin, HIGH);
  }
};

String MotorDriver::getState(){
  return String("fwd:")+ String(this->forward?"true":"false")+String(",speed:")+String(this->spd);
}

int MotorDriver::getSpeed(){
    return this->spd;
}
bool MotorDriver::getForward(){
  return this->forward;
}
