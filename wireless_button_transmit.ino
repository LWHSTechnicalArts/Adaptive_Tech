#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile
#include <avr/sleep.h>
#include <avr/wdt.h>

RH_ASK driver;
#define BUTTON_PIN 2  // Must be an interrupt-capable pin (D2 on Uno/Nano)

void wakeUp() {
    // Empty function - needed for interrupt
}

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Enable internal pull-up resistor
    pinMode(12, OUTPUT);

    digitalWrite(12, HIGH);
    delay(300);
    digitalWrite(12, LOW);

    if (!driver.init()) {
        Serial.println("RF Module Init Failed!");
    }

    // Attach interrupt to wake Arduino on button press (falling edge)
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), wakeUp, FALLING);
}

void loop() {
    Serial.println("Going to sleep...");
    delay(100); // Allow time for Serial output

    // Enable sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();  // Sleep until the button press wakes it up

    // Code resumes here after wake-up
    Serial.println("Button Pressed! Transmitting...");

    const char *msg = "Hi";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
}
