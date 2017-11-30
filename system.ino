#include "definitions.h"

// Error codes
#define TEMPERATURE_SENSOR_ERROR 1  // Temperature sensor does not send (legible) data

// Error display setup
#define ERROR_BLINK_INTERVAL 500
unsigned long int previousErrorBlinkTime = 0;
unsigned long int currentErrorBlinkState = LOW;
int errorCode = 0;

// All leds, so POST can loop over them
const uint8_t LEDS[] = {
    BLUE,
    RED,
    YELLOW,
    GREEN
};

const int sensorCount = sizeof(LEDS)/sizeof(LEDS[0]);

// Implementations

// Perform Power On Self Test
// Checks all connected sensors and actuators, and reports errors if detected
void performPost() {
    // Turn LEDS and speaker on and off
    for(int i = 0; i < sensorCount; i++) {
        digitalWrite(LEDS[i], HIGH);
    }

    tone(SPEAKER_PIN, 440, 500);

    delay(500);
        
    for(int i = 0; i < sensorCount; i++) {
        digitalWrite(LEDS[i], LOW);
    }

    

    // Check that temperature sensor sends data
    int temperature = analogRead(TEMPERATURE_PIN);
    if(temperature > 260 || temperature == 0) errorCode = 1;

    // Return 0 if all is OK
    errorCode = 0;
}

// If an error is detected by the POST, this function will display it on the board
bool notifyOnError() {
    if(errorCode == TEMPERATURE_SENSOR_ERROR) {
        // Blink red light every .5 seconds
        unsigned long int currentTime = millis();
        if(currentTime >= previousErrorBlinkTime + ERROR_BLINK_INTERVAL) {
            previousErrorBlinkTime = currentTime;
            if(currentErrorBlinkState == LOW) {
                digitalWrite(RED, HIGH);
                currentErrorBlinkState = HIGH;
            }
            else {
                digitalWrite(RED, LOW);
                currentErrorBlinkState = LOW;
            }
        }
        return true;
    }

    return false;
}