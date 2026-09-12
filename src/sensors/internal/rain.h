#pragma once
#include <ArduinoJson.h>

//

namespace ssr::internal
{
    void setupRain();
    void readRain(JsonArray &arr);
    bool isRainReadable();
}
