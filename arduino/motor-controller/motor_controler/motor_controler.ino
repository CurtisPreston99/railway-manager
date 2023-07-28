#include "MotorDriver.h"

bool spdFaster = true;
bool dir = false;
int spd = 700;
int spdMin = 5;
int spdD = 5;

MotorDriver motor1 = MotorDriver(8, 7, 6);
MotorDriver motor2 = MotorDriver(9, 10, 11);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  motor1.init();
  motor2.init();
}

void loop() {

  spdFaster ? spd+=spdD : spd-=spdD;

  if (spd >= 1000 | spd <= spdMin ) { spdFaster = !spdFaster; }
  if (spd <= spdMin ) { dir = !dir; }

  motor1.setSpeed(spd);
  motor2.setSpeed(spd);   

  motor1.setDirection(dir);
  motor2.setDirection(!dir);
//  Serial.println(motor1.getState());
  Serial.println(motor2.getState());

}
