void setup() {
  pinMode(3, OUTPUT); // LEFT MOTOR
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); // RIGHT MOTOR
  pinMode(6, OUTPUT);

}

void loop() {
  // forward for 2 secs
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  // delay(2000);
  // // backward for 2 secs
  // digitalWrite(3, LOW);
  // digitalWrite(4, HIGH);
  // digitalWrite(5, LOW);
  // digitalWrite(6, HIGH);
  // delay(2000);
  
  // axial left turn for 1 sec
  // digitalWrite(3, LOW);
  // digitalWrite(4, HIGH); // left motor backward
  // digitalWrite(5, HIGH);
  // digitalWrite(6, LOW); // right motor forward
  // delay(1000);
  // axial right turn for 1 sec
  // digitalWrite(3, HIGH);
  // digitalWrite(4, LOW); // left motor forward
  // digitalWrite(5, LOW);
  // digitalWrite(6, HIGH); // right motor backward
  // delay(1000);
  
  // radial left turn for 1 sec
  // digitalWrite(3, LOW);
  // digitalWrite(4, LOW); // left motor stop
  // digitalWrite(5, HIGH);
  // digitalWrite(6, LOW); // right motor forward
  // delay(1000);
  // // radial right turn for 1 sec
  // digitalWrite(3, HIGH);
  // digitalWrite(4, LOW); // left motor forward
  // digitalWrite(5, LOW);
  // digitalWrite(6, LOW); // right motor stop
  // delay(1000);

}
