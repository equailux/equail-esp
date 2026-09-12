#include <Arduino.h>

//

#define RAIN_PIN 17

//

void setup()
{
    Serial.begin(115200);
    pinMode(RAIN_PIN, INPUT);
}

void loop()
{
    int state = digitalRead(RAIN_PIN);
    Serial.printf("%s\n", state == HIGH ? "100%" : "0%");
    delay(250);
}
