int ls, rs;

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

  if(ls == HIGH && rs == HIGH) // both on white surface, STOP
  {
    digitalWrite (3, HIGH);
    digitalWrite (4, HIGH);
    digitalWrite (5, HIGH);
    digitalWrite (6, HIGH);
  }
  else if(ls == HIGH && rs == LOW) // stop right motor
  {
    digitalWrite (3, HIGH);
    digitalWrite (4, HIGH);
    digitalWrite (5, HIGH);
    digitalWrite (6, LOW);
  }
  else if(ls == LOW && rs == HIGH) // stop left motor
  {
    digitalWrite (3, HIGH);
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    digitalWrite (6, HIGH);
  }
  else // go forward
  {
    digitalWrite (3, HIGH);
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    digitalWrite (6, LOW);
  }


}
