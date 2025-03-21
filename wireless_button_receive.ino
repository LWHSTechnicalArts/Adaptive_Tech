#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile

#define RELAY_PIN 9  // Pin connected to relay
#define LED_PIN 8  
#define RF_RECEIVER_PIN 2  // Data pin from RF receiver


RH_ASK driver;

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);  // Internal pull-up
    pinMode(RF_RECEIVER_PIN, INPUT);
    digitalWrite(RELAY_PIN, LOW);  // Turn relay OFF
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);

    
    Serial.begin(9600);
    Serial.println("Start");

    if (!driver.init()) {
        Serial.println("RF Module Init Failed!");
    }
}

void loop() {
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) { // Check for received RF message
        buf[buflen] = '\0';  // Null-terminate the received string
        Serial.print("Message: ");
        Serial.println((char*)buf);

        if (strcmp((char*)buf, "Hi") == 0) {  // Compare strings
            Serial.println("it works");
            digitalWrite(RELAY_PIN, HIGH); // Turn relay ON
            digitalWrite(LED_PIN, HIGH);
            delay(5000);
            digitalWrite(RELAY_PIN, LOW);  // Turn relay OFF
            digitalWrite(LED_PIN, LOW);
        }
    }
}
