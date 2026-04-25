#include "dht.h"
#include "./internal/dht.h"
#include <DHTesp.h>
#include "secrets.h"

//

namespace ssr
{
    DHTesp dht;
    int dhtPin = SSR_DHT_PIN;
    unsigned long dhtAlpha = 0;
    unsigned long dhtInterval = 5000;
}

namespace ssr::internal
{
    void setupDHT()
    {
        dht.setup(dhtPin, DHTesp::DHT22);
    }

    void readDHT(JsonArray &arr)
    {
        float humidity = dht.getHumidity();
        JsonObject obj1 = arr.add<JsonObject>();
        obj1["tag"] = SSR_DHT_TAG;
        obj1["name"] = "Humidity";
        obj1["unit"] = "%";
        obj1["value"] = humidity;

        float temperature = dht.getTemperature();
        JsonObject obj2 = arr.add<JsonObject>();
        obj2["tag"] = SSR_DHT_TAG;
        obj2["name"] = "Temperature";
        obj2["unit"] = "C";
        obj2["value"] = temperature;

        dhtAlpha = millis();
    }

    bool isDHTReadable()
    {
        unsigned long ms = millis();
        return ms - dhtAlpha >= dhtInterval;
    }
}