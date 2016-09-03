#include <Arduino.h>
#include <Rtc_Pcf8563.h>
#include "DataStorage.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>

Rtc_Pcf8563 rtc;
LiquidCrystal_I2C lcd(0x27,16,2);
Display lcd_display;
DataStorage counter0("Hot",0);
DataStorage counter1("Cold",117);

void setup() {
        counter0.set_date_time(rtc);
        counter1.set_date_time(rtc);
        // инициализация данных в памяти
/*        counter0.reset_counter();
        counter1.reset_counter();
        counter0.save_counter(rtc);
        counter1.save_counter(rtc);*/
        // инициализация прерываний
        attachInterrupt(0, input_interrupt_0, RISING);
        attachInterrupt(1, input_interrupt_1, RISING);
        //инициализация экрана
        lcd.init();
        lcd.backlight();
        lcd.home();
        lcd_display.display(lcd, rtc, counter0, counter1);
}
void loop() {
        counter0.save_counter(rtc);
        counter1.save_counter(rtc);
        lcd_display.refresh(lcd, rtc, counter0, counter1);
        delay(1000);
}
void input_interrupt_0() {
        counter0.increment_counter();
}
void input_interrupt_1() {
        counter1.increment_counter();
}
