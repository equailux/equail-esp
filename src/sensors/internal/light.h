#pragma once
#include <ArduinoJson.h>

//

namespace ssr::internal
{
    void setupBH1750();
    void readBH1750(JsonArray &arr);
    bool isBH1750Readable();
}