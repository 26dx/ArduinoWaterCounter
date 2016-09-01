#include "DataStorage.h"

DataStorage::DataStorage(String _counter_description, uint8_t _EEPROM_address) {
        counter_description = _counter_description;
        counter_EEPROM_address = _EEPROM_address;
        counter_total = 0;
        for (int i = 0; i < 24; counter_hour[i++]=0);
        for (int i = 0; i < 31; counter_day[i++]=0);
        // добавить чтение записанных значений из памяти
        current_month = 0;
        current_day = 0;
        current_hour = 0;
        commit_flag = 0;
        load_counter();
}
void DataStorage::increment_counter() {
        counter_total++;
        counter_hour[0]++;
        counter_day[0]++;
        commit_flag = 1;
}
void DataStorage::reset_counter() {
        counter_total = 0;
        for (int i = 0; i < 24; counter_hour[i++]=0);
        for (int i = 0; i < 31; counter_day[i++]=0);
        commit_flag = 1;
}
void DataStorage::set_counter_value(unsigned long _value) {
        reset_counter();
        counter_total = _value;
        commit_flag = 1;
}
void DataStorage::set_date_time(Rtc_Pcf8563& _rtc) {
        current_hour = _rtc.getHour();
        current_day = _rtc.getDay();
        current_month = _rtc.getMonth();
}
unsigned long DataStorage::get_counter_value_total() {
        return counter_total;
}
uint16_t DataStorage::get_counter_value_hour(uint8_t _hour) {
        return counter_hour[_hour];
}
uint16_t DataStorage::get_counter_value_day(uint8_t _day) {
        return counter_day[_day];
}
uint16_t DataStorage::get_counter_value_month() {
        uint16_t _buffer = 0;
        for (int i = 0; i < 31; _buffer=+counter_day[i++]);
        return _buffer;
}
String DataStorage::get_counter_description() {
        return counter_description;
}
void DataStorage::save_counter(Rtc_Pcf8563& _rtc) {
        uint8_t _address = counter_EEPROM_address;
        byte _data_byte[4] = {0,0,0,0};
        // проверка изменения часа или дня!
        if (current_hour != _rtc.getHour()) {
                current_hour = _rtc.getHour();
                for (int i = 23; i > 0; i--)
                        counter_hour[i] = counter_hour[i - 1];
                counter_hour[0] = 0;
        }
        if (current_day != _rtc.getDay()) {
                current_day = _rtc.getDay();
                for (int i = 30; i > 0; i--)
                        counter_day[i] = counter_day[i - 1];
                counter_day[0] = 0;
        }
        if (current_month != _rtc.getMonth())
                current_month = _rtc.getMonth();
        if (commit_flag) {
                commit_flag = 0;
                EEPROM.write(_address++, current_hour);
                EEPROM.write(_address++, current_day);
                EEPROM.write(_address++, current_month);
                for (int i = 0; i < 4; i++) {
                        _data_byte[i] = counter_total >> (8*i);
                        EEPROM.write(_address++, _data_byte[i]);
                }
                for (int i = 0; i < 24; i++) {
                        for (int j = 0; j < 2; j++) {
                                _data_byte[j] = counter_hour[i] >> (8*j);
                                EEPROM.write(_address++, _data_byte[j]);
                        }
                }
                for (int i = 0; i < 31; i++) {
                        for (int j = 0; j < 2; j++) {
                                _data_byte[j] = counter_day[i] >> (8*j);
                                EEPROM.write(_address++, _data_byte[j]);
                        }
                }
        }
}
void DataStorage::load_counter() {
        uint8_t _address = counter_EEPROM_address;
        unsigned long _data_byte[4] = {0,0,0,0};
        current_hour = EEPROM.read(_address++);
        current_day = EEPROM.read(_address++);
        current_month = EEPROM.read(_address++);
        for (int i = 0; i < 4; _data_byte[i++] = EEPROM.read(_address++));
        counter_total = _data_byte[0] + ((_data_byte[1] << 8) & 0xFF00) + ((_data_byte[2] << 16) & 0xFF0000) + ((_data_byte[3] << 24) & 0xFF000000);
        for (int i = 0; i < 24; i++) {
                for (int j = 0; j < 2; _data_byte[j++] = EEPROM.read(_address++));
                counter_hour[i] = _data_byte[0] + ((_data_byte[1] << 8) & 0xFF00);
        }
        for (int i = 0; i < 31; i++) {
                for (int j = 0; j < 2; _data_byte[j++] = EEPROM.read(_address++));
                counter_day[i] = _data_byte[0] + ((_data_byte[1] << 8) & 0xFF00);
        }
}
