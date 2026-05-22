#include <Arduino.h>

//

void setup()
{
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(33, OUTPUT);

    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
    digitalWrite(33, HIGH);
}

void loop()
{
    digitalWrite(25, LOW);
    delay(1000);
    digitalWrite(25, HIGH);
    
    digitalWrite(26, LOW);
    delay(1000);
    digitalWrite(26, HIGH);
    
    digitalWrite(27, LOW);
    delay(1000);
    digitalWrite(27, HIGH);
    
    digitalWrite(33, LOW);
    delay(1000);
    digitalWrite(33, HIGH);
}
