#include <Arduino.h>
#include <Rtc_Pcf8563.h>
#include <EEPROM.h>

class DataStorage {
public:
        DataStorage(String _counter_description, uint8_t _EEPROM_address);
        void increment_counter();
        void reset_counter();
        void set_counter_value(long _value);

        long get_counter_value_total();
        uint16_t get_counter_value_hour(uint8_t _hour);
        uint16_t get_counter_value_day(uint8_t _day);
        uint16_t get_counter_value_month();

        String get_counter_description();

        void save_counter(Rtc_Pcf8563& _rtc);
        void load_counter();
private:
        long counter_total;
        uint16_t counter_hour[24];
        uint16_t counter_day[31];

        String counter_description;
        uint8_t EEPROM_address;

        // Время и день
        byte current_month;
        byte current_day;
        byte current_hour;
};
