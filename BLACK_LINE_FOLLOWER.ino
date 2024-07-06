int ls, rs;
int speed = 125; // Adjust this value to control the speed (0 - 255)

void setup() {
  // OUTPUT PIN FOR MOTORS
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  // INPUT PINS FOR SENSOR
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop() {
  // reading values from sensors
  ls = digitalRead(8); // store pin 8 value
  rs = digitalRead(9); // store pin 9 value

  if(ls == LOW && rs == LOW) // both on white surface, go forward
  {
    analogWrite(3, speed);
    analogWrite(4, 0);
    analogWrite(5, speed);
    analogWrite(6, 0);
  }
  else if(ls == HIGH && rs == LOW) // stop left motor
  {
    analogWrite(3, speed);
    analogWrite(4, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
  else if(ls == LOW && rs == HIGH) // stop right motor
  {
    analogWrite(3, 0);
    analogWrite(4, 0);
    analogWrite(5, speed);
    analogWrite(6, 0);
  }
  else // stop both motors
  {
    analogWrite(3, 0);
    analogWrite(4, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
}
