/*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01

    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#define enA 9
#define in1 6
#define in2 7
#define button 4

bool rotDirection = false;

int speed = 1000;
bool speedIncress = true;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:

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

  if (speed <= 400) {
    speedIncress = true;
    rotDirection = !rotDirection;
  }

  int pwmOutput = map(potValue, 0, 1023, 0, 255);  // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput);                     // Send PWM signal to L298N Enable pin
//
  // If button is pressed - change rotation direction
  if (!rotDirection) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(20);
  }
  // If button is pressed - change rotation direction
  if (rotDirection) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(20);
  }

  Serial.println(speed);
}
