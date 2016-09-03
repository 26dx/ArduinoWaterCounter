#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Rtc_Pcf8563.h>
#include "DataStorage.h"

class Display {
public:
        void display(LiquidCrystal_I2C& _lcd, Rtc_Pcf8563& _rtc, DataStorage& _counter0, DataStorage& _counter1);
        void refresh(LiquidCrystal_I2C& _lcd, Rtc_Pcf8563& _rtc, DataStorage& _counter0, DataStorage& _counter1);
};
