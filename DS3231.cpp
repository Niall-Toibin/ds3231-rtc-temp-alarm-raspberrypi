*
 * DS3231.cpp 
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#include "DS3231.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

using namespace std;

namespace een1071 {

// Function to convert BCD to Decimal
static uint8_t  bcdToDecimal (uint8_t bcd) {
   return ((bcd >> 4) * 10 + (bcd & 0x0F);
}

// Function to convert Decimal to BCD
static uint8_t decimalToBcd (uint8_t decimal) {
   return ((decimal / 10) << 4) | (decimal % 10);
}

void DS3231::readTime() {
   uint8_t sec = bcdToDecimal(readRegister(0x00));
   uint8_t min = bcdToDecimal(readRegister(0x01));
   uint8_t hour = bcdToDecimal(readRegister(0x02));
   uint8_t day = bcdToDecimal(readRegister(0x03));
   uint8_t date = bcdToDecimal(readRegister(0x04));
   uint8_t month = bcdToDecimal(readRegister(0x05));
   uint8_t year  = bcdToDecimal(readRegister(0x06));

   cout << "Time - " << (int)hours << ":" << (int)minutes << ":"
        << int(seconds) << endl;

   cout << "Date - " << (int)date << "/ " << int(month) << "/"
        << int(year) << endl;
}

float DS3231::readTemperature() {
   uint8_t l_nib = readRegister(0x11);
   uint8_t r_nib = readRegister(0x12);

   int temp = (int)l_nib;
   float temp2 = (r_nib >> 6) * 0.25f;

   return temp1 + temp2;
}
}
