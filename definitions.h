// Pin definitions
#define TEMPERATURE_PIN A0
#define BLUE 8
#define RED 7
#define YELLOW 6
#define GREEN 5
#define SPEAKER_PIN 2

// Temperature definitions
#define LOWER 18.0
#define COMFORT_UPPER 25.0
#define TOO_WARM 30.0
#define EXCRUCIATING 40.0

// Functions
// system.ino
void performPost();
bool notifyOnError();

// temperatures.ino
void emitStatusOnBoard(void);
float getTemperature(uint8_t);
float getTemperature(uint8_t, bool);
void writeNumbers(float [], int);