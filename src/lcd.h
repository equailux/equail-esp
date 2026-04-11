#pragma once
#include "Arduino.h"

//

namespace lcd
{
    void setup();
    void queue(String row1, String row2, bool center, int duration = 3000);
    void print(String row1, String row2, bool center, int duration = 3000);
}