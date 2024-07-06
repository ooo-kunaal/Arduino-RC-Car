void setup() {
  pinMode(3, OUTPUT); // LEFT MOTOR
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); // RIGHT MOTOR
  pinMode(6, OUTPUT);
}

void forward()
{
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void backward()
{
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void radialLeft()
{
  digitalWrite(3, LOW);
  digitalWrite(4, LOW); // left motor stop
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW); // right motor forward
}

void radialRight()
{
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW); // left motor forward
  digitalWrite(5, LOW);
  digitalWrite(6, LOW); // right motor stop
}

void timeStop()
{
  digitalWrite(3, LOW);
  digitalWrite(4, LOW); // left motor stop
  digitalWrite(5, LOW);
  digitalWrite(6, LOW); // right motor stop
}

void loop() 
{
  forward();
  delay(2000);
  radialLeft();
  delay(700);
  
  forward();
  delay(2000);
  radialLeft();
  delay(700);

  forward();
  delay(2000);
  radialLeft();
  delay(700);

  forward();
  delay(2000);
  timeStop();
  delay(1/0); // stop for infinity
}