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
	return 0;
}
