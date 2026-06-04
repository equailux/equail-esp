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
        digitalWrite(pumpPin, state != 0 ? LOW : HIGH);
        Serial.printf("[Actuator]: Input %d on pin %d.\n", state, pumpPin);
    }
}

namespace att::internal
{
    void setupPump()
    {
        pinMode(pumpPin, OUTPUT);
        digitalWrite(pumpPin, HIGH);
        digitalWrite(pumpPin, LOW);
        delay(100);
        digitalWrite(pumpPin, HIGH);
    }
}