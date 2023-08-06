#include <ArduinoJson.h>
#include "MotorDriver.h"

const unsigned long statusInterval = 2000; // Interval in milliseconds (e.g., 5000ms = 5 seconds)
unsigned long lastStatusMillis = 0;


String id = String("motorDriver1");
bool spdFaster = true;
bool dir = false;
int spd = 700;
int spdMin = 5;
int spdD = 5;

MotorDriver motor1 = MotorDriver(2, 4, 3);
MotorDriver motor2 = MotorDriver(6,7,5);
MotorDriver motor3 = MotorDriver(8,10,9);
MotorDriver motor4 = MotorDriver(12,13,11);

//example json {"motor_1":{"spd":100,"forward":true},"motor_2":{"spd":50,"forward":false},"motor_3":{"spd":50,"forward":false},"motor_4":{"spd":50,"forward":false}}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();
}

void loop() {
  String inputString = "";
  if (Serial.available()) {
    inputString = Serial.readString();
  }
  if (inputString.length() > 0) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, inputString);
    if (error) {

      DynamicJsonDocument errorLog(1024);
      errorLog["id"] = id;
      switch (error.code()) {
        case DeserializationError::Ok:
          errorLog["error_message"] = (F("Deserialization succeeded"));
          break;
        case DeserializationError::InvalidInput:
          errorLog["error_message"] = (F("Invalid input!"));
          break;
        case DeserializationError::NoMemory:
          errorLog["error_message"] = (F("Not enough memory"));
          break;
        default:
          errorLog["error_message"] = (F("Deserialization failed"));
          break;
      }
      serializeJson(errorLog, Serial);

    } else {
      motor1.setSpeed(doc["motor_1"]["spd"]);
      motor1.setDirection(doc["motor_1"]["forward"]);
      
      motor2.setSpeed(doc["motor_2"]["spd"]);
      motor2.setDirection(doc["motor_2"]["forward"]);
      
      motor3.setSpeed(doc["motor_3"]["spd"]);      
      motor3.setDirection(doc["motor_3"]["forward"]);

      motor4.setSpeed(doc["motor_4"]["spd"]);
      motor4.setDirection(doc["motor_4"]["forward"]);

      sendUpdate();
    }

  }else{
    unsigned long currentMillis = millis();
    if (currentMillis - lastStatusMillis  >= statusInterval) {
      // Perform the action here
      sendUpdate();

      // Update the previousMillis for the next interval
      lastStatusMillis  = currentMillis;
    }
  }

  //  spdFaster ? spd+=spdD : spd-=spdD;
  //
  //  if (spd >= 1000 | spd <= spdMin ) { spdFaster = !spdFaster; }
  //  if (spd <= spdMin ) { dir = !dir; }
  //
  //  motor1.setSpeed(spd);
  //  motor2.setSpeed(spd);
  //
  //  motor1.setDirection(dir);
  //  motor2.setDirection(!dir);

  //  Serial.println(String("motor 1:")+motor1.getState());
  //  Serial.println(String("motor 2:")+motor2.getState());
}

void sendUpdate() {
//  motor3.setSpeed(100);
//  motor3.setDirection(!motor3.getForward());  
//  motor4.setSpeed(100);
//  motor4.setDirection(!motor4.getForward());
//  
  DynamicJsonDocument motorLog(1024);
  motorLog["id"] = id;
  motorLog["motor_1"]["forward"] = motor1.getForward();
  motorLog["motor_2"]["forward"] = motor2.getForward();
  motorLog["motor_3"]["forward"] = motor3.getForward();
  motorLog["motor_4"]["forward"] = motor4.getForward();
  motorLog["motor_1"]["spd"] = motor1.getSpeed();
  motorLog["motor_2"]["spd"] = motor2.getSpeed();
  motorLog["motor_3"]["spd"] = motor3.getSpeed();
  motorLog["motor_4"]["spd"] = motor4.getSpeed();
  serializeJson(motorLog, Serial);
  Serial.println();
  Serial.flush();
}
