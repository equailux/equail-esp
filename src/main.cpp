#include <Arduino.h>
#include "Wire.h"
#include "./station.h"
#include "./websocket.h"
#include "./sensors/main.h"
#include "./actuators/main.h"
#include "./feeding/main.h"
#include "./lcd.h"

//

void setup()
{
    Serial.begin(115200);
    Wire.begin(21, 22);

    sta::setup();
    wsc::setup();
    ssr::setup();
    att::setup();
    lcd::setup();
    fed::setup();
}

void loop()
{
    fed::loop();
    if (!wsc::loop()) return;
    ssr::loop();
    att::loop();
}
