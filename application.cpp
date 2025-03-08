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
	DS3231 clock(1, 0x68) 
	
	// Displays time and date
	clock.readTime();

	float temp = clock.readTemperature;
	cout << "Temperature - " << temp << " C" << endl;
	return 0;
}
