#include <Arduino.h>
#include <Rtc_Pcf8563.h>
#include "DataStorage.h"

DataStorage counter0("Hot",0);
DataStorage counter1("Cold",117);
Rtc_Pcf8563 rtc;

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
}
void loop() {
        if (input_interrupt_flag) {
                  counter0.save_counter(rtc);
                  counter1.save_counter(rtc);
                  Serial.println(counter0.get_counter_value_day(0));
                  Serial.println(counter1.get_counter_value_dat(0));
        }
}
void input_interrupt_0() {
        input_interrupt_flag = 1;
        counter0.increment_counter();
}
void input_interrupt_1() {
        input_interrupt_flag = 1;
        counter1.increment_counter();
}
