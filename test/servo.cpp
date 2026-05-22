#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO_PIN 18
#define SERVO_MIN 500  // MG996R min pulse width (us)
#define SERVO_MAX 2500 // MG996R max pulse width (us)
#define SWEEP_DELAY 15 // ms between each degree step

Servo servo;

void setup()
{
    ESP32PWM::allocateTimer(0);
    servo.setPeriodHertz(50);
    servo.attach(SERVO_PIN, SERVO_MIN, SERVO_MAX);
}

void loop()
{
    // Sweep 0 -> 180
    for (int pos = 0; pos <= 180; pos++)
    {
        servo.write(pos);
        delay(SWEEP_DELAY);
    }

    // Sweep 180 -> 0
    for (int pos = 180; pos >= 0; pos--)
    {
        servo.write(pos);
        delay(SWEEP_DELAY);
    }
}
