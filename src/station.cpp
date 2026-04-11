#include <WiFi.h>
#include "station.h"

//

namespace sta
{
    const char *ssid = "equail";
    const char *password = "12345678";
    bool connected = false;

    //

    void onWiFiEvent(WiFiEvent_t event);

    //

    void setup()
    {
        WiFi.onEvent(onWiFiEvent);
        WiFi.begin(ssid, password);
        Serial.printf("Station WiFi connecting.\n");
    }
    
    void onWiFiEvent(WiFiEvent_t event)
    {
        switch (event)
        {
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        {
            Serial.printf("Station WiFi connected.\n");
            connected = true;
            break;
        }
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        {
            if (connected) Serial.printf("Station WiFi disconnected.\n");
            else Serial.printf("Station WiFi connecting.\n");
            connected = false;
            break;
        }
        }
    }
}


//

