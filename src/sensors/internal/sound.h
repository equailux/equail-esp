#pragma once
#include <ArduinoJson.h>

//

namespace ssr::internal
{
    void setupSound();
    void readSound(JsonArray &arr);
    bool isSoundReadable();
}