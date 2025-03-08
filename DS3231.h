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


};

} /* namespace een1071 */

#endif
