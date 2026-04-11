#pragma once
#include <ArduinoJson.h>

//

namespace ssr::internal
{
    void setupDHT();
    void readDHT(JsonArray &arr);
    bool isDHTReadable();
}