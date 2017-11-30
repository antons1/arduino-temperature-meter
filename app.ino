#include "definitions.h"

#define PRINT_TEMPS false

void setup()
{
    pinMode(BLUE, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);

    pinMode(TEMPERATURE_PIN, INPUT);
    pinMode(SPEAKER_PIN, OUTPUT);
    
    if(PRINT_TEMPS) Serial.begin(9600);

    performPost();
}

void loop()
{
    // System
    // notifyOnError returns true if it is showing an error status on the board
    // If there is an error, we don't want the main loop to run, but just show the error
    if(notifyOnError()) return;

    // Main loop
    float temperature = getTemperature(TEMPERATURE_PIN, PRINT_TEMPS);
    emitStatusOnBoard(temperature);
}