#include <Arduino.h>
#include <Rtc_Pcf8563.h>
#include "DataStorage.h"
#include <LiquidCrystal_I2C.h>

DataStorage counter0("Hot",0);
DataStorage counter1("Cold",117);
Rtc_Pcf8563 rtc;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
        counter0.reset_counter();
        counter1.reset_counter();
        // инициализация данных в памяти
        counter0.set_date_time(rtc);
        counter1.set_date_time(rtc);
        counter0.save_counter(rtc);
        counter1.save_counter(rtc);
        //инициализация экрана
        lcd.init();
        lcd.backlight();
        lcd.home();

}
void loop() {
        display(lcd, rtc, counter0, counter1);
        delay(500);
}
void display(LiquidCrystal_I2C& _lcd, Rtc_Pcf8563& _rtc, DataStorage& _counter0, DataStorage& _counter1) {
        // выводим первую строку
        _lcd.setCursor(0, 0);
        _lcd.print(_counter0.get_counter_description());
        _lcd.setCursor(0, 6);
        _lcd.print(_counter1.get_counter_description());
        _lcd.setCursor(11, 0);
        _lcd.print(_rtc.formatTime(RTCC_TIME_HM));
        // выводим вторую строку
        _lcd.setCursor(0, 1);
        _lcd.print(_counter0.get_counter_value_day(0));
        _lcd.setCursor(6, 1);
        _lcd.print(_counter1.get_counter_value_day(0));
        _lcd.setCursor(12, 1);
        _lcd.print("type")
}
