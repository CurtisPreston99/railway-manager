/*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01

    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#define enA 9
#define in1 6
#define in2 7
#define button 4

int rotDirection = 0;

int speed = 0;
bool speedIncress = true;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(button, INPUT);
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void loop() {
  int potValue = speed;  // Read potentiometer value
  speedIncress ? speed++ : speed--;
  if (speed >= 1023) {
    speedIncress = false;
  }

  if (speed <= 0) {
    speedIncress = true;
    rotDirection == 0 ? rotDirection = 1 : rotDirection = 0;
  }

  int pwmOutput = map(potValue, 0, 1023, 0, 255);  // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput);                     // Send PWM signal to L298N Enable pin

  // If button is pressed - change rotation direction
  if (rotDirection == 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    rotDirection = 1;
    delay(20);
  }
  // If button is pressed - change rotation direction
  if (rotDirection == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    rotDirection = 0;
    delay(20);
  }
}
