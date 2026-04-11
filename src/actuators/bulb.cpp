#include "bulb.h"
#include "./internal/bulb.h"
#include <Arduino.h>

//

namespace att
{
    int bulbPin = 18;

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