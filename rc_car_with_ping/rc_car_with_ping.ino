#include <NewPing.h>
#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int left = 3;
int right = 2;
int fwd = 5;
int rev = 4;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  Serial.println("RC Car");
  
  pinMode(fwd, OUTPUT);
  pinMode(rev, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  
  stop();
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  
  if (uS / US_ROUNDTRIP_CM < 5) {
    delay(50);
    return;
  }
  
  stop();
  Serial.println("Forward");
  digitalWrite(fwd, HIGH); 
  delay(1000);
  
  stop();
  Serial.println("Reverse");
  digitalWrite(rev, HIGH);
  delay(1000);

  stop();
  Serial.println("Left");
  digitalWrite(left, HIGH);
  delay(1000);
  
  stop();
  Serial.println("Right");
  digitalWrite(right, HIGH);
  delay(1000);
}

void stop()
{
  digitalWrite(fwd, LOW);
  digitalWrite(rev, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
}
