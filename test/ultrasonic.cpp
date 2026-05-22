#include <Arduino.h>

//

#define TRIG_PIN 16
#define ECHO_PIN 17

//

void setup()
{
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop()
{
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    float cm = duration * 0.0343 / 2.0;

    Serial.printf("%.3fcm\n", cm);
    delay(250);
}
