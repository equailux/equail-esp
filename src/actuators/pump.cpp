#include "pump.h"
#include "./internal/pump.h"
#include <Arduino.h>

//

namespace att
{
    int pumpPin = 19;

    //

    void writePump(int state)
    {
        digitalWrite(pumpPin, state ? LOW : HIGH);
    }
}

namespace att::internal
{
    void setupPump()
    {
        pinMode(pumpPin, OUTPUT);
        digitalWrite(pumpPin, HIGH);
    }
}