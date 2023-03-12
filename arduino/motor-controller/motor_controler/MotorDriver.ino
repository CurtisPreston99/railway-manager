#include "Arduino.h"
#include "pins_arduino.h"
#include "MotorDriver.h"
#include <pins_arduino.h>
#include <stdlib.h>

MotorDriver::MotorDriver(int fPin, int rPin, int pwmPin) {
  this->fwdPin = fPin;
  this->revPin = rPin;
  this->spdPin = pwmPin;

}

void MotorDriver::init() {
  pinMode(this->fwdPin, OUTPUT);  // 0x1 = output
  pinMode(this->revPin, OUTPUT);
  pinMode(this->spdPin, OUTPUT);
}


//speed 0-1000
void MotorDriver::setSpeed(int speed) {
  int pwmOutput = map(speed, 0, 1000, 0, 255);  // Map the spd value from 0 to 255
  analogWrite(this->spdPin, pwmOutput);         // Send PWM signal to L298N Enable pin
};

void MotorDriver::setDirection(bool fwd) {
  if (fwd) {
    digitalWrite(this->fwdPin, 1);
    digitalWrite(this->revPin, 0);
  } else {
    digitalWrite(this->fwdPin, 0);
    digitalWrite(this->revPin, 1);
  }
};

