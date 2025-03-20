#include <LowPower.h>

int potPin = A0;        // Potentiometer pin
int buttonPin = 2;      // Button pin (must be an interrupt-capable pin)
int relayPin = 7;       // Relay control pin

int potValue;
int relayTime;
volatile bool buttonPressed = false;  // Marked as volatile for interrupt use

void wakeUp() {
  buttonPressed = true;  // Set flag when button is pressed
}

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Internal pull-up

  Serial.begin(9600);

  // Attach interrupt to wake up on button press
  attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUp, FALLING);

  delay(100);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;  // Reset flag

    potValue = analogRead(potPin);  // Read potentiometer value (0-1023)
    relayTime = map(potValue, 0, 1023, 1000, 20000);  // Map to 1s - 10s

    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" - Relay On Time: ");
    Serial.println(relayTime);

    digitalWrite(relayPin, HIGH);
    delay(relayTime);
    digitalWrite(relayPin, LOW);
  }

  // Enter deep sleep mode until button press
  Serial.println("Entering Sleep Mode...");
  delay(100);  // Short delay before sleep to ensure serial output
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}
