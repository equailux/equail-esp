#include "light.h"
#include <BH1750.h>

//

namespace ssr
{
    BH1750 bh1750;
    unsigned long bh1750Alpha = 0;
    unsigned long bh1750Interval = 5000;
}

namespace ssr::internal
{
    void setupBH1750()
    {
        bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
    }

    void readBH1750(JsonArray &arr)
    {
        float light = bh1750.readLightLevel();
        JsonObject obj = arr.add<JsonObject>();
        obj["name"] = "BH1750";
        obj["unit"] = "lux";
        obj["value"] = light;

        bh1750Alpha = millis();
    }

    bool isBH1750Readable()
    {
        unsigned long ms = millis();
        return ms - bh1750Alpha >= bh1750Interval;
    }
}