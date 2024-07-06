#define echoPinRight 6       // Echo Pin Of Right HC-SR04
#define trigPinRight 7       // Trig Pin Of Right HC-SR04
#define echoPinFront 8       // Echo Pin Of Front HC-SR04
#define trigPinFront 9       // Trig Pin Of Front HC-SR04
#define echoPinLeft 10       // Echo Pin Of Left HC-SR04
#define trigPinLeft 11       // Trig Pin Of Left HC-SR04
#define irRightPin 12        // IR Sensor Right Pin
#define irLeftPin 13         // IR Sensor Left Pin

struct FuzzySet {
  float stop;
  float slow;
  float medium;
  float fast;
  float full_speed;
};

struct FiringStrengths {
  float rule1;
  float rule2;
  float rule3;
  float rule4;
  float rule5;
  float rule6;
  float rule7;
  float rule8;
  float rule9;
};

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);     // Set Motor Pins As O/P
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(trigPinRight, OUTPUT);   // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPinRight, INPUT);    // Set Echo Pin As I/P To Receive Reflected Waves
  pinMode(trigPinLeft, OUTPUT);   
  pinMode(echoPinLeft, INPUT);    
  pinMode(trigPinFront, OUTPUT);   
  pinMode(echoPinFront, INPUT);    
  pinMode(irRightPin, INPUT);      // Set IR Sensor Pins As I/P
  pinMode(irLeftPin, INPUT);
}

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);       // Transmit Waves For 10us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH); // Receive Reflected Waves
  long distance = duration / 58.2;        // Get Distance in cm
  return distance;
}

// Membership functions for distance
float close(float distance) {
  if (distance <= 10) return 1.0;
  else if (distance > 10 && distance <= 15) return (15 - distance) / 5.0;
  else return 0.0;
}

float near(float distance) {
  if (distance <= 10 || distance >= 20) return 0.0;
  else if (distance > 10 && distance <= 13) return (distance - 10) / 3.0;
  else if (distance > 13 && distance <= 17) return 1.0;
  else if (distance > 17 && distance <= 20) return (20 - distance) / 3.0;
  else return 0.0;
}

float far(float distance) {
  if (distance <= 17) return 0.0;
  else if (distance > 17 && distance <= 20) return (distance - 17) / 3.0;
  else return 1.0;
}

// Membership functions for speed
float stop(float speed) {
  return (speed < 100) ? 1.0 : 0.0;
}

float slow(float speed) {
  if (speed < 100) return 0.0;
  else if (speed >= 100 && speed <= 120) return (speed - 100) / 20.0;
  else if (speed > 120 && speed <= 150) return 1.0;
  else if (speed > 150 && speed <= 170) return (160 - speed) / 20.0;
  else return 0.0;
}

float medium(float speed) {
  if (speed < 150 || speed > 220) return 0.0;
  else if (speed >= 150 && speed <= 170) return (speed - 150) / 20.0;
  else if (speed >= 170 && speed <= 200) return 1.0;
  else if (speed > 200 && speed <= 220) return (200 - speed) / 20.0;
  else return 0.0;
}

float fast(float speed) {
  if (speed < 200 || speed >= 250) return 0.0;
  else if (speed >= 200 && speed <= 220) return (speed - 200) / 20.0;
  else if (speed >= 220 && speed <= 250) return 1.0;
  else if (speed > 250 && speed <= 255) return (255 - speed) / 5.0;
  else return 0.0;
}

float full_speed(float speed) {
  return (speed == 255) ? 1.0 : 0.0;
}


// Helper function to calculate the minimum of three values
float min3(float a, float b, float c) {
  return min(a, min(b, c));
}

// Helper function to calculate the maximum of three values
float max3(float a, float b, float c) {
  return max(a, max(b, c));
}

FiringStrengths calculateFiringStrengths(float frontDist, float leftDist, float rightDist) {
  FiringStrengths strengths;

  float frontClose = close(frontDist);
  float frontNear = near(frontDist);
  float frontFar = far(frontDist);

  float leftClose = close(leftDist);
  float leftNear = near(leftDist);
  float leftFar = far(leftDist);

  float rightClose = close(rightDist);
  float rightNear = near(rightDist);
  float rightFar = far(rightDist);

  // Rule evaluation
  strengths.rule1 = min3(frontNear, leftNear, rightFar);
  strengths.rule2 = min3(frontNear, leftFar, rightNear);
  strengths.rule3 = min3(frontNear, leftNear, rightNear);
  strengths.rule4 = min3(frontNear, leftFar, rightFar);

  strengths.rule5 = min3(frontFar, leftNear, rightFar);
  strengths.rule6 = min3(frontFar, leftFar, rightNear);
  strengths.rule7 = min3(frontFar, leftNear, rightNear);
  strengths.rule8 = min3(frontFar, leftFar, rightFar);

  strengths.rule9 = max3(frontClose, leftClose, rightClose);

  return strengths;
}

float defuzzifyLeft(FiringStrengths strengths) {
  FuzzySet fuzzySetL;
  fuzzySetL.stop = strengths.rule9;
  fuzzySetL.slow = max(strengths.rule2, strengths.rule3);
  fuzzySetL.medium = max(strengths.rule6, strengths.rule7);
  fuzzySetL.fast = max3(strengths.rule1, strengths.rule4, strengths.rule5);
  fuzzySetL.full_speed = strengths.rule8;
  return defuzzify(fuzzySetL);
}

float defuzzifyRight(FiringStrengths strengths) {
  FuzzySet fuzzySetR;
  fuzzySetR.stop = strengths.rule9;
  fuzzySetR.slow = max3(strengths.rule1, strengths.rule3, strengths.rule4);
  fuzzySetR.medium = max(strengths.rule5, strengths.rule7);
  fuzzySetR.fast = max(strengths.rule2, strengths.rule6);
  fuzzySetR.full_speed = strengths.rule8;
  return defuzzify(fuzzySetR);
}

// Defuzzification using the centroid method
float defuzzify(FuzzySet fuzzySet) {
  float numerator = 0;
  float denominator = 0;
  for (int i = 0; i <= 255; i++) {
    float membership = max(min(stop(i), fuzzySet.stop), 
                           max(min(slow(i), fuzzySet.slow), 
                           max(min(medium(i), fuzzySet.medium), 
                           max(min(fast(i), fuzzySet.fast), 
                               min(full_speed(i), fuzzySet.full_speed)))));
    numerator += i * membership;
    denominator += membership;
  }
  if (denominator == 0) return 0; // Avoid division by zero
  return numerator / denominator;
}

void setMotorSpeeds(float speed_L, float speed_R) {
  analogWrite(2, 0);
  analogWrite(3, speed_L);
  analogWrite(4, 0);
  analogWrite(5, speed_R);
}

void stopAndReverse() {
  digitalWrite(2, LOW); // Stop motors
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(500);

  // IR Sensors: Check if space is available at the back
  bool rightClear = digitalRead(irRightPin) == HIGH; // Assuming HIGH indicates clear space
  bool leftClear = digitalRead(irLeftPin) == HIGH;   // Assuming HIGH indicates clear space
  Serial.print("IR Right Sensor: "); Serial.println(rightClear ? "Clear" : "Blocked");
  Serial.print("IR Left Sensor: "); Serial.println(leftClear ? "Clear" : "Blocked");

  if (rightClear && leftClear) {
    Serial.println("No obstacles detected. Moving backward.");
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(500); // Move backward for 0.5 second
  } else {
    Serial.println("Obstacle detected at the back. Stopping.");
  }

  // Stop motors again
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(250);
}

void loop() {
  float leftDistance = measureDistance(trigPinLeft, echoPinLeft);
  float frontDistance = measureDistance(trigPinFront, echoPinFront);
  float rightDistance = measureDistance(trigPinRight, echoPinRight);

  Serial.print("Left Distance: "); Serial.println(leftDistance);
  Serial.print("Front Distance: "); Serial.println(frontDistance);
  Serial.print("Right Distance: "); Serial.println(rightDistance);

  FiringStrengths strengths = calculateFiringStrengths(frontDistance, leftDistance, rightDistance);

  float speed_L = defuzzifyLeft(strengths);
  float speed_R = defuzzifyRight(strengths);

  // Log the centroid values for left and right motor speeds in a format suitable for Serial Plotter
  Serial.print("Speed_L:");
  Serial.print(speed_L);
  Serial.print(" Speed_R:");
  Serial.println(speed_R);

  // Serial.print("Speed L: "); Serial.println(speed_L);
  // Serial.print("Speed R: "); Serial.println(speed_R);
  
  if(speed_L > speed_R) {
    Serial.print("Turning Right");
  } else if(speed_L == speed_R) {
    Serial.print("Forward");
  } else {
    Serial.print("Turning Left");
  }

  if (speed_L <= 100 || speed_R <= 100) {
    Serial.println("stop & reverse");
    stopAndReverse();
  } else {
    setMotorSpeeds(speed_L, speed_R);
  }
  // Use a constant delay for scanning
  delay(200); // 0.2-second interval
}
