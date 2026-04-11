#pragma once
#include <ArduinoJson.h>

//

namespace ssr
{
    void onRead(void (*hook)(JsonArray));
}