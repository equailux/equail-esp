#include <Arduino.h>

//

#define SOUND_DETECTOR_PIN 35

//

void setup()
{
    Serial.begin(115200);
    pinMode(SOUND_DETECTOR_PIN, INPUT);
}

void loop()
{
    float noise = analogRead(SOUND_DETECTOR_PIN);
    Serial.printf("%.3f\n", noise);
}
