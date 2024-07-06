#include <Servo.h> 
Servo Myservo;

#define trigPin 11           // Trig Pin Of HC-SR04
#define echoPin 10           // Echo Pin Of HC-SR04
#define irRightPin 8         // IR Sensor Right Pin
#define irLeftPin 9          // IR Sensor Left Pin
long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);     // Set Motor Pins As O/P
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(trigPin, OUTPUT); // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPin, INPUT);  // Set Echo Pin As I/P To Receive Reflected Waves
  pinMode(irRightPin, INPUT); // Set IR Sensor Pins As I/P
  pinMode(irLeftPin, INPUT);
  Myservo.attach(12);       // Attach Servo to Pin 12
}

void forward() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void backward() {
  // Check if space is available at the back
  bool rightClear = digitalRead(irRightPin) == HIGH; // HIGH indicates clear space
  bool leftClear = digitalRead(irLeftPin) == HIGH;   // HIGH indicates clear space
  Serial.print("IR Right Sensor: ");
  Serial.println(rightClear ? "Clear" : "Blocked");
  Serial.print("IR Left Sensor: ");
  Serial.println(leftClear ? "Clear" : "Blocked");
  if (rightClear && leftClear) {
    Serial.println("No obstacles detected. Moving backward.");
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  } else {
    stop();
    Serial.println("Obstacle detected at the back. Stopping.");
  }
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

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);       // Transmit Waves For 10us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Receive Reflected Waves
  long distance = duration / 58.2;   // Get Distance in cm
  return distance;
}

void loop() 
{
  distance = measureDistance(); // Measure distance
  delay(10);

  if (distance > 15) { // Condition For Absence Of Obstacle            
    Myservo.write(90);
    forward(); // Move Forward
  } else if ((distance < 10) && (distance > 0)) 
  { // Condition For Presence Of Obstacle
    Serial.println("Obstacle detected in front. Stopping and scanning...");
    stop(); // Stop                
    delay(100);
  
    Myservo.write(0); // Look left
    delay(500);
    long leftDistance = measureDistance(); // Measure left distance
    Myservo.write(180); // Look right
    delay(500);
    long rightDistance = measureDistance(); // Measure right distance
    Myservo.write(90); // Look forward
    delay(500);
    
    if (leftDistance > rightDistance) {
      Serial.println("More clearance to the left. Moving backward and turning left.");
      backward(); // Move Backward
      delay(500);
      left(); // Move Left     
      delay(500);
    } else {
      Serial.println("More clearance to the right. Moving backward and turning right.");
      backward(); // Move Backward
      delay(500);
      right(); // Move Right     
      delay(500);
    }
  }
}
