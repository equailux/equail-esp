#pragma once
#include <ArduinoJson.h>

//

namespace ssr::internal
{
    void setupUltrasonic();
    void readUltrasonic(JsonArray &arr);
    bool isUltrasonicReadable();
}