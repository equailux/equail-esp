#include "sequence.h"
#include "../actuators/motor.h"
#include "../actuators/servo.h"
#include <Arduino.h>

//

namespace fed::internal
{
    enum class Step
    {
        Idle,
        OpenServo1,
        WaitServo1,
        CloseServo1,
        StartMotorForward,
        WaitMotorForward,
        StopMotorForward,
        OpenServo2,
        WaitServo2,
        CloseServo2,
        StartMotorReverse,
        WaitMotorReverse,
        StopMotorReverse,
    };

    // writeServo uses 181+ to address servo 2 and applies state % 180.
    const int servo1OpenInput = 180;
    const int servo1CloseInput = 0;
    const int servo2OpenInput = 359;
    const int servo2CloseInput = 360;

    Step step = Step::Idle;
    Command command = {0, 0, 0};
    unsigned long stepStartedAt = 0;

    //

    void waitFor(Step next)
    {
        stepStartedAt = millis();
        step = next;
    }

    bool hasElapsed(unsigned long duration)
    {
        return millis() - stepStartedAt >= duration;
    }

    void startSequence(const Command &next)
    {
        command = next;
        step = Step::OpenServo1;
        stepStartedAt = millis();

        Serial.printf(
            "Feeding automation started: servo1=%lu, servo2=%lu, stepper=%lu.\n",
            command.servo1Ms,
            command.servo2Ms,
            command.stepperMs);
    }

    void loopSequence()
    {
        switch (step)
        {
        case Step::Idle:
        {
            break;
        }
        case Step::OpenServo1:
        {
            att::writeServo(servo1OpenInput);
            waitFor(Step::WaitServo1);
            break;
        }
        case Step::WaitServo1:
        {
            if (hasElapsed(command.servo1Ms))
                step = Step::CloseServo1;
            break;
        }
        case Step::CloseServo1:
        {
            att::writeServo(servo1CloseInput);
            step = Step::StartMotorForward;
            break;
        }
        case Step::StartMotorForward:
        {
            att::writeMotor(1);
            waitFor(Step::WaitMotorForward);
            break;
        }
        case Step::WaitMotorForward:
        {
            if (hasElapsed(command.stepperMs))
                step = Step::StopMotorForward;
            break;
        }
        case Step::StopMotorForward:
        {
            att::writeMotor(0);
            step = Step::OpenServo2;
            break;
        }
        case Step::OpenServo2:
        {
            att::writeServo(servo2OpenInput);
            waitFor(Step::WaitServo2);
            break;
        }
        case Step::WaitServo2:
        {
            if (hasElapsed(command.servo2Ms))
                step = Step::CloseServo2;
            break;
        }
        case Step::CloseServo2:
        {
            att::writeServo(servo2CloseInput);
            step = Step::StartMotorReverse;
            break;
        }
        case Step::StartMotorReverse:
        {
            att::writeMotor(-1);
            waitFor(Step::WaitMotorReverse);
            break;
        }
        case Step::WaitMotorReverse:
        {
            if (hasElapsed(command.stepperMs))
                step = Step::StopMotorReverse;
            break;
        }
        case Step::StopMotorReverse:
        {
            att::writeMotor(0);
            step = Step::Idle;
            Serial.printf("Feeding automation finished.\n");
            break;
        }
        }
    }

    bool isSequenceRunning()
    {
        return step != Step::Idle;
    }
}
