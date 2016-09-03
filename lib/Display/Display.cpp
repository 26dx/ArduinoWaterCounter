#include "Display.h"

void Display::display(LiquidCrystal_I2C& _lcd, Rtc_Pcf8563& _rtc, DataStorage& _counter0, DataStorage& _counter1) {
        _lcd.clear();
        // выводим первую строку
        _lcd.setCursor(0, 0);
        _lcd.print(_counter0.get_counter_description());
        _lcd.setCursor(6, 0);
        _lcd.print(_counter1.get_counter_description());
        _lcd.setCursor(11, 0);
        _lcd.print(_rtc.formatTime(RTCC_TIME_HM));
        // выводим вторую строку
        _lcd.setCursor(0, 1);
        _lcd.print(_counter0.get_counter_value_day(0));
        _lcd.setCursor(6, 1);
        _lcd.print(_counter1.get_counter_value_day(0));
        _lcd.setCursor(11, 1);
        _lcd.print("10L/D");
}
void Display::refresh(LiquidCrystal_I2C& _lcd, Rtc_Pcf8563& _rtc, DataStorage& _counter0, DataStorage& _counter1) {
  // выводим первую строку
  _lcd.setCursor(0, 0);
  _lcd.print(_counter0.get_counter_description());
  _lcd.setCursor(6, 0);
  _lcd.print(_counter1.get_counter_description());
  _lcd.setCursor(11, 0);
  _lcd.print(_rtc.formatTime(RTCC_TIME_HM));
  // выводим вторую строку
  _lcd.setCursor(0, 1);
  _lcd.print(_counter0.get_counter_value_day(0));
  _lcd.setCursor(6, 1);
  _lcd.print(_counter1.get_counter_value_day(0));
  _lcd.setCursor(11, 1);
  _lcd.print("10L/D");
}
