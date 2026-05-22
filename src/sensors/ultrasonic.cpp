#include "ultrasonic.h"
#include "secrets.h"

//

namespace ssr
{
    int ultrasonicTrigPin = SSR_ULTRASONIC_TRIG_PIN;
    int ultrasonicEchoPin = SSR_ULTRASONIC_ECHO_PIN;
    float ultrasonicDistance = 30;
    
    unsigned long ultrasonicAlpha = 0;
    unsigned long ultrasonicInterval = 5000;
}

namespace ssr::internal
{
    void setupUltrasonic()
    {
        pinMode(ultrasonicTrigPin, OUTPUT);
        pinMode(ultrasonicEchoPin, INPUT);
    }

    void readUltrasonic(JsonArray &arr)
    {
        digitalWrite(ultrasonicTrigPin, HIGH);
        delayMicroseconds(20);
        digitalWrite(ultrasonicTrigPin, LOW);

        long duration = pulseIn(ultrasonicEchoPin, HIGH, 30000);
        float cm = duration * 0.0343 / 2.0;
        float displacement = ultrasonicDistance - cm;

        JsonObject obj = arr.add<JsonObject>();
        obj["tag"] = SSR_ULTRASONIC_TAG;
        obj["name"] = "Water Level";
        obj["unit"] = "cm";
        obj["value"] = displacement <= 0 ? 0 : displacement;

        ultrasonicAlpha = millis();
    }

    bool isUltrasonicReadable()
    {
        unsigned long ms = millis();
        return ms - ultrasonicAlpha >= ultrasonicInterval;
    }
}