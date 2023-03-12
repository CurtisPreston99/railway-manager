#include "MotorDriver.h"

bool spdFaster = true;
bool dir = false;
int spd = 0;


MotorDriver motor1 = MotorDriver(6, 7, 8);
MotorDriver motor2 = MotorDriver(3, 4, 5);

void setup() {
  // put your setup code here, to run once:
  motor1.init();
  motor2.init();
}

void loop() {
  spdFaster ? spd++ : spd--;

  if (spd >= 1000 | spd <= 500) { spdFaster = !spdFaster; }
  if (spd <= 500) { dir = !dir; }

  motor1.setSpeed(spd);
  motor2.setSpeed(spd);

  motor1.setDirection(dir);
  motor2.setDirection(!dir);
}
