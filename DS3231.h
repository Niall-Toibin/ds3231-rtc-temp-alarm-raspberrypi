X/*
 * DS3231.h
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Niall Toibin
 */

#ifndef DS3231_H_
#define DS3231_H_
#include"I2CDevice.h"

namespace een1071 {

class DS3231:public I2CDevice{
public:
   // Constructor
   DS3231(unsigned int bus, unsigned int device);
   // Read and display time
   void readTime();

   // Return temperature
   float readTemperature();


};

} /* namespace een1071 */

#endif
