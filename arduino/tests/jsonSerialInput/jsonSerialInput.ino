#include "ArduinoJson.h"

char input;
using namespace std;

String inputString = "";
// {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038],"bool":true}
// {"led":true}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(2000);

  Serial.println("Type something!");
}

void loop() {
  if (Serial.available()) {
    inputString = Serial.readString();
  }
  if (inputString.length() > 0) {
    Serial.println(inputString);
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, inputString);
    // const char* sensor = doc["sensor"];
    // long time = doc["time"];
    // double latitude = doc["data"][0];
    // double longitude = doc["data"][1];
    // bool test = doc["bool"];
    // Serial.println(sensor);
    // Serial.println(time);
    // Serial.println(latitude, 6);
    // Serial.println(longitude, 6);
    // Serial.println(test);

    bool ledStatus = doc["led"];
    Serial.println(ledStatus);
    if (ledStatus) {
      Serial.println("true");

      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    } else {
      Serial.println("false");
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    }

    inputString = "";
  }
}