#include "lcd.h"
#include "LiquidCrystal_I2C.h"
#include "Arduino.h"
#include "vector"

//

namespace lcd
{
    int rows = 2;
    int cols = 16;
    LiquidCrystal_I2C lcd(0x27, cols, rows);

    int length = 0;
    unsigned long alpha = 0;

    std::vector<String> row1s = {};
    std::vector<String> row2s = {};
    std::vector<bool> centers = {};
    std::vector<int> durations = {};

    //

    void queue(String row1, String row2, bool center, int duration);
    void print(String row1, String row2, bool center, int duration);

    //
    
    void setup()
    {
        lcd.init();
        lcd.backlight();
        lcd.setCursor(0, 0);
        print("E-Quail", "Welcome", true);
        Serial.printf("Lcd initialized successfully.\n");
    }

    void loop()
    {
        unsigned long ms = millis();
        if (ms - alpha < length || row1s.empty()) return;
        
        print(row1s.front(), row2s.front(), centers.front(), durations.front());
        row1s.erase(row1s.begin());
        row2s.erase(row2s.begin());
        centers.erase(centers.begin());
        durations.erase(durations.begin());
    }

    void queue(String row1, String row2, bool center, int duration) 
    {
        row1s.push_back(row1);
        row2s.push_back(row2);
        centers.push_back(center);
        durations.push_back(duration);
    }

    void print(String row1, String row2, bool center, int duration) 
    {
        size_t r1len = row1.length();
        int r1gap = cols - r1len;
        int r1pad = r1gap > 0 ? floor(r1gap / 2) : 0;
        int r1end = cols - (r1len + r1pad);
        if (center) for (int i = 0; i < r1pad; i++) row1 = " " + row1;
        if (center) for (int i = 0; i < r1end; i++) row1 += " ";
        lcd.setCursor(0, 0);
        lcd.print(row1);
        
        size_t r2len = row2.length();
        int r2gap = cols - r2len;
        int r2pad = r2gap > 0 ? floor(r2gap / 2) : 0;
        int r2end = cols - (r2len + r2pad);
        if (center) for (int i = 0; i < r2pad; i++) row2 = " " + row2;
        if (center) for (int i = 0; i < r2end; i++) row2 += " ";
        lcd.setCursor(0, 1);
        lcd.print(row2);
    }
}