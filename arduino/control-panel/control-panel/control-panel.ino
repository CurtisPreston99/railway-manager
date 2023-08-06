#include <ArduinoJson.h>
#include "SliderControl.h"
String id = String("controler1");
const unsigned long statusInterval = 1000;  // Interval in milliseconds (e.g., 5000ms = 5 seconds)
unsigned long lastStatusMillis = 0;

int SliderControl1Button = 6;
int SliderControl2Button = 5;
int SliderControl3Button = 4;
int SliderControl4Button = 3;
int SliderControl5Button = 2;

SliderControl Slider1 = SliderControl(A0, SliderControl1Button);
SliderControl Slider2 = SliderControl(A1, SliderControl2Button);
SliderControl Slider3 = SliderControl(A2, SliderControl3Button);
SliderControl Slider4 = SliderControl(A3, SliderControl4Button);
SliderControl Slider5 = SliderControl(A4, SliderControl5Button);

void setup() {
  Serial.begin(9600);  // Initialize the serial communication for debugging
}

void loop() {

  Slider1.update();
  Slider2.update();
  Slider3.update();
  Slider4.update();
  Slider5.update();

  unsigned long currentMillis = millis();
  if (currentMillis - lastStatusMillis >= statusInterval) {
    // Perform the action here
    sendUpdate();

    // Update the previousMillis for the next interval
    lastStatusMillis = currentMillis;
  }
}


void sendUpdate() {

  DynamicJsonDocument controlLog(1024);
  controlLog["id"] = id;
  controlLog["slider1"]["value"] = Slider1.getSlider();
  controlLog["slider1"]["fwd"] = Slider1.getForward();

  controlLog["slider2"]["value"] = Slider2.getSlider();
  controlLog["slider2"]["fwd"] = Slider2.getForward();

  controlLog["slider3"]["value"] = Slider3.getSlider();
  controlLog["slider3"]["fwd"] = Slider3.getForward();

  controlLog["slider4"]["value"] = Slider4.getSlider();
  controlLog["slider4"]["fwd"] = Slider4.getForward();

  controlLog["slider5"]["value"] = Slider5.getSlider();
  controlLog["slider5"]["fwd"] = Slider5.getForward();

  serializeJson(controlLog, Serial);
  Serial.println();
  Serial.flush();
}
