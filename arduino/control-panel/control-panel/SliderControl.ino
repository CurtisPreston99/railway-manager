#include "Arduino.h"

SliderControl::SliderControl(int sliderPin, int reversingPin) {
  this->sliderPin = sliderPin;
  this->reversingPin = reversingPin;
  this->forward = false;
  pinMode(reversingPin, INPUT_PULLUP);
}

void SliderControl::reverseDirection() {
  this->forward = !this->forward;
}

void SliderControl::init() {}

void SliderControl::setDirection(bool fwd) {
  this->forward = fwd;
}

void SliderControl::update() {
  int button = digitalRead(this->reversingPin);
  if (button == 0 && !this->pressed) {
    Serial.println("switched");
    this->reverseDirection();
    this->pressed = true;
  }
  if (button == 1) {
    this->pressed = false;
  }
}

int SliderControl::getSlider() {
  int slider = analogRead(this->sliderPin);  // Read the value from the potentiometer (0 to 1023)
  return map(slider, 0, 1023, 0, 100);
}
bool SliderControl::getForward() {
  return this->forward;
}
