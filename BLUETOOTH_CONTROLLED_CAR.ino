int command;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  
  // Initialize motor control pins as outputs
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  // Print a start-up message
  Serial.println("RC Car Control Ready!");
}

void forward() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  Serial.println("Moving Forward");
}

void back() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  Serial.println("Moving Backward");
}

void left() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  Serial.println("Turning Left");
}

void right() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  Serial.println("Turning Right");
}

void Stop() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  Serial.println("Stopping");
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read(); // Read the incoming byte
    Serial.print("Received command: ");
    Serial.println(command);

    switch (command) {
      case 70:  // ASCII for 'F'
        forward();
        break;
      case 102: // ASCII for 'f'
        Stop();
        break;
      case 66:  // ASCII for 'B'
        back();
        break;
      case 98:  // ASCII for 'b'
        Stop();
        break;
      case 76:  // ASCII for 'L'
        left();
        break;
      case 108: // ASCII for 'l'
        Stop();
        break;
      case 82:  // ASCII for 'R'
        right();
        break;
      case 114: // ASCII for 'r'
        Stop();
        break;
      default:
        Serial.println("Invalid command");
        Stop();
        break;
    }
  }
}