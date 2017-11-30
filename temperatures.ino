#include "definitions.h"

// Which LED is currently displayed. 
int currentLight = GREEN;

// Implementations

// Takes the measured temperature, and turns on the correct LEDs and maybe sound
// Thresholds are defined in definitions.h
void emitStatusOnBoard(float temperature) {
    if(temperature <= LOWER) {
        beepIfTempChange(currentLight, BLUE);
        digitalWrite(currentLight, LOW);
        currentLight = BLUE;
        warningBeep(1200);
    }
    else if (temperature > LOWER && temperature <= COMFORT_UPPER) {
        beepIfTempChange(currentLight, GREEN);
        digitalWrite(currentLight, LOW);
        currentLight = GREEN;
    }
    else if (temperature > COMFORT_UPPER && temperature <= TOO_WARM) {
        beepIfTempChange(currentLight, YELLOW);
        digitalWrite(currentLight, LOW);
        currentLight = YELLOW;
    }
    else if (temperature > TOO_WARM && temperature <= EXCRUCIATING) {
        beepIfTempChange(currentLight, RED);
        digitalWrite(currentLight, LOW);
        currentLight = RED;
    }
    else if (temperature > EXCRUCIATING) {
        beepIfTempChange(currentLight, RED);
        digitalWrite(currentLight, LOW);
        currentLight = RED;
        warningBeep(1000);
    }

    digitalWrite(currentLight, HIGH);
}

// Makes a small beep each time the temperature crosses a threshold
// TODO: This is annoying because the sensor is inaccurate and cand start
// oscillating over a threshold so that there is a continouus sound
// This needs to be changed so that does not happen
// 30.11.2017
void beepIfTempChange(int current, int next) {
    //if (current != next) tone(SPEAKER_PIN, 200, 4);
}

// Sends out a short beep each second.
// Used on temperatures lower than lowest threshold, and higher than highest.
unsigned long int previousWarningBeepTime = 0;
const int warningBeepInterval = 1000;
void warningBeep(int freq) {
    unsigned long int currentTime = millis();

    if(currentTime >= previousWarningBeepTime + warningBeepInterval) {
        tone(SPEAKER_PIN, freq, 100);
        previousWarningBeepTime = currentTime;
    }
}

// Reads the temperature without printing result. See float getTemperature(uint8_t, bool)
float getTemperature(uint8_t pin)
{
    return getTemperature(pin, false);
}

// Reads temperature and returns result, and prints result to Serial if printValues is true
float getTemperature(uint8_t pin, bool printValues)
{
    float sensorADC = analogRead(TEMPERATURE_PIN);
    float sensorV = (sensorADC / 1024.0) * 5.0;
    float sensorTemp = (sensorV - .5) * 100.0;

    if (printValues)
    {
        float numberArray[] = {sensorADC, sensorV, sensorTemp};
        writeNumbers(numberArray, 3);
    }

    return sensorTemp;
}

// Writes the numbers in numbers[] with a \t between each.
void writeNumbers(float numbers[], int size)
{
    for (int i = 0; i < size; i++)
    {
        Serial.print(numbers[i]);
        Serial.print("\t");
    }
    Serial.println();
}