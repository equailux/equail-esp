#include "main.h"
#include "./internal/hook.h"
#include "./internal/dht.h"
#include "./internal/light.h"
#include "./internal/limitter.h"
#include "./internal/ultrasonic.h"
#include <ArduinoJson.h>

//

namespace ssr
{
    void setup()
    {
        ssr::internal::setupDHT();
        ssr::internal::setupBH1750();
        ssr::internal::setupLimitter();
        ssr::internal::setupUltrasonic();
    }

    void loop()
    {
        JsonDocument doc;
        JsonArray arr = doc.to<JsonArray>();

        if (ssr::internal::isDHTReadable()) ssr::internal::readDHT(arr);
        if (ssr::internal::isBH1750Readable()) ssr::internal::readBH1750(arr);
        if (ssr::internal::isLimitterReadable()) ssr::internal::readLimitter(arr);
        if (ssr::internal::isUltrasonicReadable()) ssr::internal::readUltrasonic(arr);
        if (arr.size() > 0) ssr::internal::invokeOnReadHooks(arr);
    }
}