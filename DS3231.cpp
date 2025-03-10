/*
 * DS3231.cpp 
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#include "DS3231.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <cstdint>

using namespace std;

namespace een1071 {

// Function to convert BCD to Decimal
static uint8_t  bcdToDecimal (uint8_t bcd) {
   return ((bcd >> 4) * 10 + (bcd & 0x0F));
}

// Function to convert Decimal to BCD
static uint8_t decimalToBcd (uint8_t decimal) {
   return ((decimal / 10) << 4) | (decimal % 10);
}

// Constructor (Member Initalization) calls base class
DS3231::DS3231(unsigned int bus, unsigned int device) : I2CDevice(bus, device)
{

}

void DS3231::readTime() {
   // Defining variables for time registers. Converts each BCD value to decimal.
   uint8_t sec = bcdToDecimal(readRegister(0x00));
   uint8_t min = bcdToDecimal(readRegister(0x01));
   uint8_t hour = bcdToDecimal(readRegister(0x02));
   uint8_t day = bcdToDecimal(readRegister(0x03));
   uint8_t date = bcdToDecimal(readRegister(0x04));
   uint8_t month = bcdToDecimal(readRegister(0x05));
   uint8_t year  = bcdToDecimal(readRegister(0x06));

   cout << "Time - " << (int)hour << ":" << (int)min << ":"
        << int(sec) << endl;

   cout << "Date - " << (int)date << "/ " << int(month) << "/"
        << int(year) << endl;
}

float DS3231::readTemperature() {
   // 0x11 represents signed integer of temperature
   // 0x12 2 MSb's represent the decimal portion of temperature
   int8_t l_nib = static_cast<int8_t>(this->readRegister(0x11));
   uint8_t r_nib = readRegister(0x12);


   // Float has range [0, 0.25, 0.5, 0.75]
   float temp2 = (r_nib >> 6) * 0.25f; 

   return temp + temp2;
}

void DS3231::setTime(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t min, uint8_t sec) {
   // Convert values to BCD
   uint8_t yearBcd = decimalToBcd(year);
   uint8_t monthBcd = decimalToBcd(month);
   uint8_t dateBcd = decimalToBcd(date);
   uint8_t hourBcd = decimalToBcd(hour);
   uint8_t minBcd = decimalToBcd(min);
   uint8_t secBcd = decimalToBcd(sec);

   // Write each value to appropriate register
   writeRegister(0x00, secBcd);
   writeRegister(0x01, minBcd);
   writeRegister(0x02, hourBcd);
   writeRegister(0x04, dateBcd);
   writeRegister(0x05, monthBcd);
   writeRegister(0x06, yearBcd);

}
void DS3231::setAlarm1(uint8_t alarm1sec, uint8_t alarm1min, uint8_t alarm1hour, uint8_t alarm1val, bool dydt) {
   uint8_t secBcd = decimalToBcd(alarm1sec);
   uint8_t minBcd = decimalToBcd(alarm1min);
   uint8_t hourBcd = decimalToBcd(alarm1hour);
   uint8_t alarm1valBcd = decimalToBcd(alarm1val);

   // If dydt = 1, alarm1 value is day of week.
   if (dydt == true) {
      alarm1valBcd |= 0x40;
   }

   // Clear mask bits
   secBcd &= 0x7F;
   minBcd &= 0x7F;
   hourBcd &= 0x7F;
   alarm1valBcd &= 0x7F;

   writeRegister(0x07, secBcd);
   writeRegister(0x08, minBcd);
   writeRegister(0x09, hourBcd);
   writeRegister(0x0A, alarm1valBcd);

}

// Read and print registers 0x07, 0x08, 0x09, 0x0A.
void DS3231::readAlarm1() {
   // Read registers, removing bit 7
   uint8_t bcdsec = readRegister(0x07) & 0x7F;
   uint8_t bcdmin = readRegister(0x08) & 0x7F;
   uint8_t bcdhour = readRegister(0x09) & 0x7F;
   uint8_t bcdval = readRegister(0x0A) & 0x7F;

   // Convert register values to decimal
   uint8_t alarm1sec = bcdToDecimal(bcdsec);
   uint8_t alarm1min = bcdToDecimal(bcdmin);
   uint8_t alarm1hour = bcdToDecimal(bcdhour & 0x3F);
   uint8_t alarm1val = bcdToDecimal(bcdval & 0x3F);


   cout << "Alarm 1" << endl;
   cout << "Day or Date = " << int(alarm1val) << ". Hour = " << int(alarm1hour) << ". Minute = " << int(alarm1min) << ". Second = " << int(alarm1sec) << endl;
}


// Set Alarm 2.
void DS3231::setAlarm2(uint8_t alarm2min, uint8_t alarm2hour,
   uint8_t alarm2val, bool dydt) {
      // Convert values to BCD.
      uint8_t minBcd = decimalToBcd(alarm2min);
      uint8_t hourBcd = decimalToBcd(alarm2hour);
      uint8_t alarm2valBcd = decimalToBcd(alarm2val);

      // Alarm value is day of week
      if (dydt == true) {
         alarm2valBcd |= 0x40;
      }

      hourBcd &= 0xBF; // 24 hour mode

      // Clear mask bits for exact mode
      minBcd &= 0x7F;
      hourBcd &= 0x7F;
      alarm2valBcd &= 0x7F;

      writeRegister(0x0B, minBcd);
      writeRegister(0x0C, hourBcd);
      writeRegister(0x0D, alarm2valBcd);

}

void DS3231::readAlarm2() {
   uint8_t bcdmin = readRegister(0x0B) & 0x7F;
   uint8_t bcdhour = readRegister(0x0C) & 0x7F;
   uint8_t bcdval = readRegister(0x0D) & 0x7F;

   // Convert bcd values to decimal
   uint8_t alarm2min = bcdToDecimal(bcdmin);
   uint8_t alarm2hour = bcdToDecimal(bcdhour & 0x3F);
   uint8_t alarm2val = bcdToDecimal(bcdval & 0x3F);

   cout << "Alarm 2." << endl;
   cout <<"Day/date = " << int(alarm2val) <<". Hour = " << int(alarm2hour) << ". Minute = " << int(alarm2min) << endl;
}

void DS3231::enableInterrupts(bool enAlarm1, bool enAlarm2) {
   uint8_t controlRegister = readRegister(0x0E);

   // Set ICTN to 1
   controlRegister |= 0x04;

   // Enable alarms
   if (enAlarm1 == true) {
      // Set A1IE
      controlRegister |= 0x01;
   }
   else {
      // Clear A1IE
      controlRegister &= ~0x01;
   }
   if (enAlarm2 == true) {
      // Set A2IE
      controlRegister |= 0x02;
   }
   else {
      // Clear A2IE
      controlRegister &= ~0x02;
   }
   // Write to control
   writeRegister(0x0E, controlRegister);

}
}




