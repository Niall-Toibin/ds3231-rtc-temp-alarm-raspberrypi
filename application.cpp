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

	// Testing alarm 1.
	rtcmodule.setAlarm1(10, 11, 12, 13, false);
	cout << "Set alarm 1 for 12.11.10 on date 13" << endl;
	rtcmodule.readAlarm1();

	// Testing alarm 2
	rtcmodule.setAlarm2(11, 12, 3, false);
	cout << "Set alarm 2 for 12.11 on date 3" << endl;
	rtcmodule.readAlarm2();
	return 0;
}
