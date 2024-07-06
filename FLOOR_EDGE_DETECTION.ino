int ls, rs;

void forward() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void backward() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void right() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void left() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void stop() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}


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

  if(ls == LOW && rs == LOW) // both detecting floor
  {
    forward();
  }
  else if(ls == HIGH && rs == LOW) // left turn
  {
    stop();
    delay(100);
    left();
  }
  else if(ls == LOW && rs == HIGH) // right turn
  {
    stop();
    delay(100);
    right();
  }
  else // both detecting edge
  {
    stop();
    delay(100);
    backward();
    delay(300);
    stop();
    delay(100);
  }
}
