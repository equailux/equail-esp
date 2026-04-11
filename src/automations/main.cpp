#include "main.h"
#include "./internal/feeding.h"
#include "./internal/watering.h"

//

namespace aut
{
    void setup()
    {
        aut::internal::setupFeeding();
        aut::internal::setupWatering();
    }

    void loop()
    {
        aut::internal::loopFeeding();
        aut::internal::loopWatering();
    }
}