#include "sound.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "secrets.h"

//

namespace ssr
{
    int soundPin = SSR_SOUND_PIN;
    float soundMin = 4095.0;
    float soundMax = 0.0;
    unsigned long soundAlpha = 0;
    unsigned long soundInterval = 50;
}

namespace ssr::internal
{
    void setupSound()
    {
        pinMode(soundPin, INPUT);
        
        for (int i = 0; i < 2000; i++)
        {
            float raw = (float)analogRead(soundPin);
            soundMin = raw < soundMin ? raw : soundMin;
            soundMax = raw > soundMax ? raw : soundMax;
            delay(1);
        }

        Serial.printf("Sound sensor calibration: %0.0f - %0.0f\n", soundMin, soundMax);
    }

    void readSound(JsonArray &arr)
    {
        float total = 0.0;
        for (int i = 0; i < 100; i++)
        {
            total += (float)analogRead(soundPin);
            delay(10);
        }

        float avg = total / 100.0;
        float base = soundMax - soundMin;
        float diff = avg - soundMin;
        float percent = diff <= 0 ? 0 : diff / base * 100.0;
        float value = percent > 100 ? 100 : percent;

        JsonObject obj = arr.add<JsonObject>();
        obj["tag"] = SSR_SOUND_TAG;
        obj["name"] = "Noise Level";
        obj["unit"] = "%";
        obj["value"] = value;

        soundAlpha = millis();
    }

    bool isSoundReadable()
    {
        unsigned long ms = millis();
        return ms - soundAlpha >= soundInterval;
    }
}