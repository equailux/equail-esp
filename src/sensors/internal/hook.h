#pragma once
#include <ArduinoJson.h>

//

namespace ssr::internal
{
    void invokeOnReadHooks(JsonArray &arr);
}