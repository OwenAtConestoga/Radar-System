#include <Servo.h>

// Servo object
Servo myservo;

// Ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 6;

// Variables
int pos = 0;       // Servo position
long duration;     // Duration of the ultrasonic pulse
int distance;      // Calculated distance

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach the servo to pin 9
  myservo.attach(9);

  // Set trigPin as OUTPUT and echoPin as INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos); // Move servo to the current position
    delay(15);          // Wait for the servo to reach the position

    // Measure distance
    distance = getDistance();

    // Print the servo position and distance to the serial monitor
    Serial.print("Servo Position: ");
    Serial.print(pos);
    Serial.print(" degrees, Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Sweep the servo back from 180 to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos); // Move servo to the current position
    delay(15);          // Wait for the servo to reach the position

    // Measure distance
    distance = getDistance();

    // Print the servo position and distance to the serial monitor
    Serial.print("Servo Position: ");
    Serial.print(pos);
    Serial.print(" degrees, Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}

// Function to measure distance using the ultrasonic sensor
int getDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Convert time to distance (in cm)

  return distance;
}
