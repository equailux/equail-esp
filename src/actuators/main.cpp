#include "main.h"
#include "bulb.h"
#include "motor.h"
#include "pump.h"
#include "servo.h"
#include "./internal/bulb.h"
#include "./internal/motor.h"
#include "./internal/pump.h"
#include "./internal/servo.h"
#include <ArduinoJson.h>
#include "ws.h"
#include "secrets.h"

//

namespace att
{
    void onUpdate(JsonArray data)
    {
        for (JsonObject actuator : data)
        {
            String tag = actuator["tag"].as<String>();
            tag.trim();
            tag.toLowerCase();
            if (tag.length() <= 0) continue;

            int input = actuator["input"].as<int>();
            if (ATT_BULB_ENABLED && tag.startsWith(ATT_BULB_TAG)) att::writeBulb(input);
            if (ATT_MOTOR_ENABLED && tag.startsWith(ATT_MOTOR_TAG)) att::writeMotor(input);
            if (ATT_PUMP_ENABLED && tag.startsWith(ATT_PUMP_TAG)) att::writePump(input);
            if (ATT_SERVO_ENABLED && tag.startsWith(ATT_SERVO_TAG)) att::writeServo(input);
            Serial.printf("Actuator input %d to %s.\n", input, tag.c_str());
        }
    }

    void setup()
    {
        if (ATT_BULB_ENABLED) att::internal::setupBulb();
        if (ATT_MOTOR_ENABLED) att::internal::setupMotor();
        if (ATT_PUMP_ENABLED) att::internal::setupPump();
        if (ATT_SERVO_ENABLED) att::internal::setupServo();

        ws::onEvent("Actuator", ws::EventQuery::Update, onUpdate);
    }

    void loop()
    {
    }
}