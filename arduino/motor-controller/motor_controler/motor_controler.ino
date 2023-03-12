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
spdFaster?
  // put your main code here, to run repeatedly:
  motor1.init();
  motor2.init();
}
