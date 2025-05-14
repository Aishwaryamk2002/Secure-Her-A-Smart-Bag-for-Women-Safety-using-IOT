#include <SoftwareSerial.h>

// Pin Definitions
#define BUZZER D5
#define BUTTON D6
#define BT_RX D7
#define BT_TX D8
#define MIC_PIN A0  // KY-037 analog output connected to A0

// Bluetooth Serial
SoftwareSerial btSerial(BT_RX, BT_TX);

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  btSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("System Initialized. Waiting for input...");
}

void loop() {
  int buttonState = digitalRead(BUTTON);
  int micValue = analogRead(MIC_PIN);

  // Threshold for loud sound (you can test & adjust)
  int soundThreshold = 100;

  Serial.print("Mic Value: ");
  Serial.println(micValue);

  // Emergency triggered by button press
  if (buttonState == LOW) {
    Serial.println("Button Pressed - Emergency!");
    digitalWrite(BUZZER, HIGH);
    btSerial.println("Help Me! (Triggered by Button)");
    delay(5000);
    digitalWrite(BUZZER, LOW);
  }

  // Emergency triggered by loud sound
  else if (micValue > soundThreshold) {
    Serial.println("Loud sound detected - Emergency!");
    digitalWrite(BUZZER, HIGH);
    btSerial.println("Help Me! (Triggered by Sound)");
    delay(5000);
    digitalWrite(BUZZER, LOW);
  }

  delay(200);  // Small delay to reduce serial flooding
}
