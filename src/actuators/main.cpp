#include "main.h"
#include "./internal/bulb.h"
#include "./internal/motor.h"
#include "./internal/pump.h"
#include "./internal/servo.h"

//

namespace att
{
    void setup()
    {
        att::internal::setupBulb();
        att::internal::setupMotor();
        att::internal::setupPump();
        att::internal::setupServo();
    }

    void loop()
    {
        
    }
}