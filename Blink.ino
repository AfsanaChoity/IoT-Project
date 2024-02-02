#include <Servo.h>
Servo servoMain;

const int TRIG_PIN = 8;             // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = 7;             // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int LED_PIN = 9;              // Arduino pin connected to LED's pin
const int DISTANCE_THRESHOLD = 20;  // distance in centimeter
const int BUZZER_PIN = 10;

float duration_us, distance_cm;

void setup() {
  Serial.begin(9600);            // initialize serial port
  pinMode(TRIG_PIN, OUTPUT);     // set Arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);      // set Arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);      // set Arduino pin to output mode
  pinMode(BUZZER_PIN, OUTPUT);
  servoMain.attach(6);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if (distance_cm < DISTANCE_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);   // turn on LED
    tone(BUZZER_PIN, 1000);        // Start the buzzer at 1000Hz
    delay(200);                    // Buzz for 200 milliseconds
    noTone(BUZZER_PIN);
    servoMain.write(180);          // move servo to 180 degrees
    delay(3000);                   // wait for 3 seconds (adjust as needed)
  } else {
    digitalWrite(LED_PIN, LOW);    // turn off LED
    servoMain.write(45);           // move servo back to 0 degrees
  }

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}