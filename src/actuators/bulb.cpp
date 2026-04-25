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
        digitalWrite(bulbPin, state ? LOW : HIGH);
    }
}

namespace att::internal
{
    void setupBulb()
    {
        pinMode(bulbPin, OUTPUT);
        digitalWrite(bulbPin, HIGH);
    }
}