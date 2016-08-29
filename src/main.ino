#include <Arduino.h>
#include "DataStorage.h"

DataStorage counter0("Hot",0);
DataStorage counter1("Cold",117);

void setup() {
        counter0.reset_counter();
        counter1.reset_counter();
}
void loop() {

}
