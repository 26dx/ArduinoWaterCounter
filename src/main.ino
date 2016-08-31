#include <Arduino.h>
#include <Rtc_Pcf8563.h>
#include "DataStorage.h"
#include <LiquidCrystal_I2C.h>

DataStorage counter0("Hot",0);
DataStorage counter1("Cold",117);
Rtc_Pcf8563 rtc;
LiquidCrystal_I2C lcd(0x27,16,2);

volatile uint8_t input_interrupt_flag = 0;

void setup() {
        counter0.set_date_time(rtc);
        counter1.set_date_time(rtc);
        // инициализация данных в памяти
        counter0.reset_counter();
        counter1.reset_counter();
        counter0.save_counter(rtc);
        counter1.save_counter(rtc);
        // инициализация прерываний
        attachInterrupt(0, input_interrupt_0, RISING);
        attachInterrupt(1, input_interrupt_1, RISING);
        //инициализация экрана
        lcd.init();
        lcd.backlight();
        lcd.home();
}
void loop() {
        if (input_interrupt_flag) {
                counter0.save_counter(rtc);
                counter1.save_counter(rtc);
                Serial.println(counter0.get_counter_value_day(0));
                Serial.println(counter1.get_counter_value_day(0));
        }
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
        _lcd.print("type");
}
void input_interrupt_0() {
        input_interrupt_flag = 1;
        counter0.increment_counter();
}
void input_interrupt_1() {
        input_interrupt_flag = 1;
        counter1.increment_counter();
}
