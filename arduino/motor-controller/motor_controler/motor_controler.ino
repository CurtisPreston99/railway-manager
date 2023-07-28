#include <ArduinoJson.h>
#include "MotorDriver.h"

String id = String("motorDriver1");
bool spdFaster = true;
bool dir = false;
int spd = 700;
int spdMin = 5;
int spdD = 5;

MotorDriver motor1 = MotorDriver(8, 7, 6);
MotorDriver motor2 = MotorDriver(9, 10, 11);

//example json {"motor_1":{"spd":100,"forward":true},"motor_2":{"spd":50,"forward":false}}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  motor1.init();
  motor2.init();
}

void loop() {
  String inputString = "";
  if (Serial.available()) {
    inputString = Serial.readString();
  }
  if (inputString.length() > 0) {
    Serial.println(inputString);
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, inputString);
    if(error){
      
      DynamicJsonDocument errorLog(1024);
      errorLog["id"]=id;
      switch (error.code()) {
        case DeserializationError::Ok:
            errorLog["error_message"]=(F("Deserialization succeeded"));
            break;
        case DeserializationError::InvalidInput:
            errorLog["error_message"]=(F("Invalid input!"));
            break;
        case DeserializationError::NoMemory:
            errorLog["error_message"]=(F("Not enough memory"));
            break;
        default:
            errorLog["error_message"]=(F("Deserialization failed"));
            break;
        }
        serializeJson(errorLog, Serial);
        Serial.println();

    }else{
      motor1.setSpeed(doc["motor_1"]["spd"]);
      motor2.setSpeed(doc["motor_2"]["spd"]);
  
      motor1.setDirection(doc["motor_1"]["forward"]);
      motor2.setDirection(doc["motor_2"]["forward"]);
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
  DynamicJsonDocument motorLog(1024);
  motorLog["id"]=id;
  motorLog["motor_1"]["forward"] = motor1.getForward();
  motorLog["motor_2"]["forward"] = motor2.getForward();
  motorLog["motor_1"]["spd"] = motor1.getSpeed();
  motorLog["motor_2"]["spd"] = motor2.getSpeed();
  serializeJson(motorLog, Serial);
  Serial.println();
//  Serial.println(String("motor 1:")+motor1.getState());
//  Serial.println(String("motor 2:")+motor2.getState());
}
