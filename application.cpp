/*
 * Application.cpp
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#include <iostream>
#include "DS3231.h"
#include <unistd.h>
#include <pthread.h>

using namespace std;
using namespace een1071;

int main() {
    // Calls constructor to create clock object
	// Uses I2C Bus 1.

	DS3231 rtcmodule(1, 0x68); 
	
	// Displays time and date
	rtcmodule.readTime();

	float temp = rtcmodule.readTemperature();
	cout << "Temperature before set - " << temp << " C" << endl;

	rtcmodule.setTime(25, 3, 8, 14, 47, 20);
	cout << "Time set to 14.47.20. Date set to 8/3/25" << endl;

	rtcmodule.readTime();

	// Set alarm 1 to trigger 10 seconds after time is set
	rtcmodule.setAlarm1(30, 47, 14, 8, false);
	cout << "Set alarm 1 for 14.47.30 on date 8" << endl;
	rtcmodule.readAlarm1();

	rtcmodule.enableInterrupts(true, false);
	cout << "Interrupt enabled (alarm 1)" << endl;

	sleep(30);
}
