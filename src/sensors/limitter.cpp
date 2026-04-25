#include "limitter.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "secrets.h"

//

namespace ssr
{
    int limitter1Pin = SSR_LIMITTER1_PIN;
    int limitter2Pin = SSR_LIMITTER2_PIN;
    unsigned long limitterAlpha = 0;
    unsigned long limitterInterval = 50;
}

namespace ssr::internal
{
    void setupLimitter()
    {
        pinMode(limitter1Pin, INPUT_PULLUP);
        pinMode(limitter2Pin, INPUT_PULLUP);
    }

    void readLimitter(JsonArray &arr)
    {
        int l1 = digitalRead(limitter1Pin);
        int l2 = digitalRead(limitter2Pin);

        JsonObject obj1 = arr.add<JsonObject>();
        obj1["tag"] = String(SSR_LIMITTER_TAG) + "1";
        obj1["name"] = "Limit Switch1";
        obj1["unit"] = "";
        obj1["value"] = l1 == LOW;

        JsonObject obj2 = arr.add<JsonObject>();
        obj2["tag"] = String(SSR_LIMITTER_TAG) + "2";
        obj2["name"] = "Limit Switch2";
        obj2["unit"] = "";
        obj2["value"] = l2 == LOW;

        limitterAlpha = millis();
    }

    bool isLimitterReadable()
    {
        unsigned long ms = millis();
        return ms - limitterAlpha >= limitterInterval;
    }
}