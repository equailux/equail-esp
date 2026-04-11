#pragma once
#include <ArduinoJson.h>

//

namespace ssr::internal
{
    void setupLimitter();
    void readLimitter(JsonArray &arr);
    bool isLimitterReadable();
}