#include "motor.h"
#include "./internal/motor.h"
#include <Arduino.h>
#include "secrets.h"

//

namespace att
{
    int motorPin1 = ATT_MOTOR_PIN1;
    int motorPin2 = ATT_MOTOR_PIN2;
    int motorPinPwma = ATT_MOTOR_PIN_PWMA;
    int motorPinStby = ATT_MOTOR_PIN_STBY;

    int motorPwmCh = 0;
    int motorPwmRes = 20000;
    int motorPwmFreq = 8;

    //

    void writeMotor(int state)
    {
        digitalWrite(motorPin1, state >= 1 ? HIGH : state <= -1 ? LOW : LOW);
        digitalWrite(motorPin2, state >= 1 ? LOW : state <= -1 ? HIGH : LOW);
        ledcWrite(motorPwmCh, state >= 1 ? 180 : state <= -1 ? 180 : 0);
    }
}

namespace att::internal
{
    void setupMotor()
    {
        pinMode(motorPin1, OUTPUT);
        pinMode(motorPin2, OUTPUT);
        pinMode(motorPinStby, OUTPUT);
        digitalWrite(motorPinStby, HIGH);
        ledcSetup(motorPwmCh, motorPwmFreq, motorPwmRes);
        ledcAttachPin(motorPinPwma, motorPwmCh);
    }
}