#pragma once

//

namespace att
{
    extern int motorPin1;
    extern int motorPin2;
    extern int motorPinPwma;
    extern int motorPinStby;

    //
    
    void writeMotor(int state);
}