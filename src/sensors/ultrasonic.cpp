#include "ultrasonic.h"

//

namespace ssr
{
    int ultrasonicTrigPin = 16;
    int ultrasonicEchoPin = 17;
    float ultrasonicDistance = 50;
    float ultrasonicDisplacement = 5;
    
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
        float percent = (ultrasonicDistance - cm) / ultrasonicDisplacement;

        JsonObject obj = arr.add<JsonObject>();
        obj["name"] = "Water Level";
        obj["unit"] = "%";
        obj["value"] = percent;

        ultrasonicAlpha = millis();
    }

    bool isUltrasonicReadable()
    {
        unsigned long ms = millis();
        return ms - ultrasonicAlpha >= ultrasonicInterval;
    }
}