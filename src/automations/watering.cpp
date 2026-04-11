#include "watering.h"
#include "./internal/watering.h"
#include "../sensors/hook.h"
#include "../actuators/pump.h"
#include <ArduinoJson.h>

//

namespace aut
{
    bool wateringEnabled = true;
    int wateringDuration = 2000;
    int wateringThreshold = 50;
    unsigned long wateringAlpha = 0;
}

namespace aut::internal
{
    void onReadWaterLevel(JsonArray arr);

    //

    void setupWatering()
    {
        ssr::onRead(onReadWaterLevel);
    }

    void loopWatering()
    {
        unsigned long ms = millis();
        if (ms - wateringAlpha >= wateringDuration) att::writePump(0);
    }

    void onReadWaterLevel(JsonArray arr)
    {
        if (!wateringEnabled) return;
        for (JsonObject obj : arr) 
        {
            if (!obj["name"].as<String>().equals("Water Level")) continue;
            int level = obj["value"].as<int>();
            
            if (level > wateringThreshold) continue;
            att::writePump(1);
            wateringAlpha = millis();
        }
    }
}