#include "main.h"
#include "./internal/hook.h"
#include "./internal/dht.h"
#include "./internal/light.h"
#include "./internal/ultrasonic.h"
#include "./internal/sound.h"
#include <ArduinoJson.h>
#include "ws.h"
#include "secrets.h"

//

namespace ssr
{
    void onRetrieve(JsonArray data)
    {
        JsonDocument doc;
        JsonArray arr = doc.to<JsonArray>();

        bool dht = false, bh = false, lim = false, ultra = false, sound = false;

        for (JsonObject sensor : data)
        {
            String tag = sensor["tag"].as<String>();
            tag.trim();
            tag.toLowerCase();

            if (tag.length() <= 0) continue;
            if (SSR_DHT_ENABLED && tag.startsWith(SSR_DHT_TAG)) dht = true;
            if (SSR_BH1750_ENABLED && tag.startsWith(SSR_BH1750_TAG)) bh = true;
            if (SSR_ULTRASONIC_ENABLED && tag.startsWith(SSR_ULTRASONIC_TAG)) ultra = true;
            if (SSR_SOUND_ENABLED && tag.startsWith(SSR_SOUND_TAG)) sound = true;
        }

        if (dht) ssr::internal::readDHT(arr);
        if (bh) ssr::internal::readBH1750(arr);
        if (ultra) ssr::internal::readUltrasonic(arr);
        if (sound) ssr::internal::readSound(arr);

        if (arr.size() > 0) ssr::internal::invokeOnReadHooks(arr);
    }

    void setup()
    {
        if (SSR_DHT_ENABLED) ssr::internal::setupDHT();
        if (SSR_BH1750_ENABLED) ssr::internal::setupBH1750();
        if (SSR_ULTRASONIC_ENABLED) ssr::internal::setupUltrasonic();
        if (SSR_SOUND_ENABLED) ssr::internal::setupSound();

        ws::onEvent("Reading", ws::EventQuery::Retrieve, onRetrieve);
        ssr::onRead([](JsonArray arr) { ws::emit("Reading", arr, ws::EventQuery::Create); });
    }

    void loop()
    {
    }
}