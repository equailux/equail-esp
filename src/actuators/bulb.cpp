#include "bulb.h"
#include "./internal/bulb.h"
#include <Arduino.h>
#include "secrets.h"

//

namespace att
{
    int bulbPin = ATT_BULB_PIN;

    //

    void writeBulb(int state)
    {
        digitalWrite(bulbPin, state != 0 ? LOW : HIGH);
        Serial.printf("[Actuator]: Input %d on pin %d.\n", state, bulbPin);
    }
}

namespace att::internal
{
    void setupBulb()
    {
        pinMode(bulbPin, OUTPUT);
        digitalWrite(bulbPin, HIGH);
        digitalWrite(bulbPin, LOW);
        delay(100);
        digitalWrite(bulbPin, HIGH);
    }
}