#include "main.h"
#include "bulb.h"
#include "pump.h"
#include "./internal/bulb.h"
#include "./internal/pump.h"
#include <ArduinoJson.h>
#include "ws.h"
#include "secrets.h"

//

namespace att
{
    void onUpdate(JsonArray data)
    {
        for (JsonObject actuator : data)
        {
            String tag = actuator["tag"].as<String>();
            tag.trim();
            tag.toLowerCase();

            int input = actuator["input"].as<int>();
            if (ATT_BULB_ENABLED && tag.startsWith(ATT_BULB_TAG)) att::writeBulb(input);
            if (ATT_PUMP_ENABLED && tag.startsWith(ATT_PUMP_TAG)) att::writePump(input);
            Serial.printf("Actuator input %d to %s.\n", input, tag.c_str());
        }
    }

    void setup()
    {
        if (ATT_BULB_ENABLED) att::internal::setupBulb();
        if (ATT_PUMP_ENABLED) att::internal::setupPump();

        ws::onEvent("Actuator", ws::EventQuery::Update, onUpdate);
    }

    void loop()
    {
    }
}