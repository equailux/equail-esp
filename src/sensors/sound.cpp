#include "sound.h"
#include <Arduino.h>
#include <ArduinoJson.h>

//

namespace ssr
{
    int soundPin = 33;
    unsigned long soundAlpha = 0;
    unsigned long soundInterval = 50;
}

namespace ssr::internal
{
    void setupSound()
    {
        pinMode(soundPin, INPUT);
    }

    void readSound(JsonArray &arr)
    {
        int value = digitalRead(soundPin);
        JsonObject obj = arr.add<JsonObject>();
        obj["name"] = "Sound Detector";
        obj["unit"] = "%";
        obj["value"] = value == LOW;

        soundAlpha = millis();
    }

    bool isSoundReadable()
    {
        unsigned long ms = millis();
        return ms - soundAlpha >= soundInterval;
    }
}