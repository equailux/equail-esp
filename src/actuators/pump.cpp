#include "pump.h"
#include "./internal/pump.h"
#include <Arduino.h>
#include "secrets.h"

//

namespace att
{
    int pumpPin = ATT_PUMP_PIN;

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