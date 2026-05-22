#include <Arduino.h>
#include "secrets.h"

//

int motorPin1 = ATT_MOTOR_PIN1;
int motorPin2 = ATT_MOTOR_PIN2;

//

void setupMotor()
{
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, HIGH);
}

void writeMotor(int state)
{
    digitalWrite(motorPin1, state >= 1 ? HIGH : state <= -1 ? LOW
                                                            : HIGH);
    digitalWrite(motorPin2, state >= 1 ? LOW : state <= -1 ? HIGH
                                                           : HIGH);
}

//

void setup()
{
    Serial.begin(115200);
    setupMotor();
}

void loop()
{
    writeMotor(1);
    Serial.printf("writeMotor(1)\n");
    delay(5000);

    writeMotor(0);
    Serial.printf("writeMotor(0)\n");
    delay(5000);

    writeMotor(-1);
    Serial.printf("writeMotor(-1)\n");
    delay(5000);

    writeMotor(0);
    Serial.printf("writeMotor(0)\n");
    delay(5000);
}
