#include "rain.h"
#include <Arduino.h>
#include "secrets.h"

//

namespace ssr
{
    int rainPin = SSR_RAIN_PIN;

    unsigned long rainAlpha = 0;
    unsigned long rainInterval = 5000;
}

namespace ssr::internal
{
    void setupRain()
    {
        pinMode(rainPin, INPUT);
    }

    void readRain(JsonArray &arr)
    {
        float value = digitalRead(rainPin) == HIGH ? 100.0 : 0.0;

        JsonObject obj = arr.add<JsonObject>();
        obj["tag"] = SSR_RAIN_TAG;
        obj["name"] = "Water Level";
        obj["unit"] = "%";
        obj["value"] = value;

        rainAlpha = millis();
    }

    bool isRainReadable()
    {
        unsigned long ms = millis();
        return ms - rainAlpha >= rainInterval;
    }
}
