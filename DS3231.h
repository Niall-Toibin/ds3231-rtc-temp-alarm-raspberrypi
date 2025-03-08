/*
 * DS3231.h
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Niall Toibin
 */

#ifndef DS3231_H_
#define DS3231_H_
#include"I2CDevice.h"
#include <cstdint>

namespace een1071 {

class DS3231 : public I2CDevice{
public:
   // Constructor
   DS3231(unsigned int bus, unsigned int device);
   // Read and display time
   void readTime();

   // Return temperature
   float readTemperature();

   void setTime(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t min, uint8_t sec);

   // Sets alarm 1, only for an exact match on time
   // Will add other modes later if feasible
   void setAlarm1(uint8_t alarm1sec, uint8_t alarm1min, uint8_t alarm1hour, uint8_t alarm1val, bool dydt = false);
   void readAlarm1();

   // Set alarm 2.
   void setAlarm2(uint8_t alarm2min, uint8_t alarm2hour, uint8_t alarm2val, bool dydt = false);
   void readAlarm2();

   void enableInterrupts(bool alarm1, bool alarm2);

};

} /* namespace een1071 */

#endif
