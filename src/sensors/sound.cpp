#include "sound.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "secrets.h"

//

namespace ssr
{
    int soundPin = SSR_SOUND_PIN;
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
        float raw = (float)analogRead(soundPin);
        float value = raw == 0 ? 0 : raw / 4095 * 100.0;
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