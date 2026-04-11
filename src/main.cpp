#include <Arduino.h>
#include "Wire.h"
#include "./station.h"

//

void setup()
{
    Serial.begin(115200);
    Wire.begin(21, 22);

    sta::setup();
}

void loop()
{
}
