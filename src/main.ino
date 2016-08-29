#include <Arduino.h>
#include <Rtc_Pcf8563.h>
#include "DataStorage.h"

DataStorage counter0("Hot",0);
DataStorage counter1("Cold",117);
Rtc_Pcf8563 rtc;

void setup() {
        counter0.reset_counter();
        counter1.reset_counter();
        // инициализация данных в памяти
        counter0.set_date_time(rtc);
        counter1.set_date_time(rtc);
        counter0.save_counter(rtc);
        counter1.save_counter(rtc);
}
void loop() {

}
