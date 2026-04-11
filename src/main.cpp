#include <Arduino.h>
#include "Wire.h"
#include "./station.h"
#include "./websocket.h"
#include "./sensors/main.h"
#include "./actuators/main.h"
#include "./automations/main.h"

//

void setup()
{
    Serial.begin(115200);
    Wire.begin(21, 22);

    sta::setup();
    wsc::setup();
    ssr::setup();
    att::setup();
    aut::setup();
}

void loop()
{
    if (!wsc::loop()) return;
    ssr::loop();
    att::loop();
    aut::loop();
}
