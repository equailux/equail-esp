#include "main.h"
#include "command.h"
#include "sequence.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "secrets.h"
#include "ws.h"

//

namespace fed
{
    void onCreate(JsonArray data)
    {
        if (isRunning())
        {
            Serial.printf("Feeding command ignored: automation already running.\n");
            return;
        }

        Command command = {0, 0, 0};

        if (!internal::readCommand(data, command))
        {
            Serial.printf("Feeding command ignored: invalid data.\n");
            return;
        }

        if (!ATT_SERVO_ENABLED || !ATT_MOTOR_ENABLED)
        {
            Serial.printf("Feeding command ignored: servo or motor actuator disabled.\n");
            return;
        }

        internal::startSequence(command);
    }

    void setup()
    {
        ws::onEvent("Feed", ws::EventQuery::Create, onCreate);
    }

    void loop()
    {
        internal::loopSequence();
    }

    bool isRunning()
    {
        return internal::isSequenceRunning();
    }
}
