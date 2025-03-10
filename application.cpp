/*
 * Application.cpp
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 * Modified by: Student Name
 */

#include <iostream>
#include "DS3231.h"
#include <unistd.h>
#include <pthread.h>
#include <gpiod.h> 
#include "I2CDevice.h"

#define gpio_chip "/dev/gpiochip0"
#define sqw_in 27
#define led_out 17

using namespace std;
using namespace een1071;

int main() {
    // Calls constructor to create clock object
	// Uses I2C Bus 1.

	DS3231 rtcmodule(1, 0x68); 
	
	// Displays time and date
	rtcmodule.readTime();

	float temp = rtcmodule.readTemperature();
	cout << "Temperature- " << temp << " C" << endl;

	rtcmodule.setTime(25, 3, 8, 14, 47, 20);
	cout << "Time set to 14.47.20. Date set to 8/3/25" << endl;

	rtcmodule.readTime();

	// Set alarm 1 to trigger 20 seconds after time is set
	rtcmodule.setAlarm1(40, 47, 14, 8, false);
	cout << "Set alarm 1 for 14.47.30 on date 8" << endl;
	rtcmodule.readAlarm1();

	rtcmodule.enableInterrupts(true, false);
	cout << "Interrupt enabled (alarm 1)" << endl;

	// Open GPIO chip
	gpiod_chip *chip = gpiod_chip_open(gpio_chip);

	// Set alarm input line
	gpiod_line *alarm_line = gpiod_chip_get_line(chip, sqw_in);

	gpiod_line_request_falling_edge_events(alarm_line, "sqw/int");

    gpiod_line *led_line = gpiod_chip_get_line(chip, led_out);
    gpiod_line_request_output(led_line, "led", 0);

	while (true) {
        gpiod_line_event_wait(alarm_line, NULL); 
        struct gpiod_line_event line_event;
        gpiod_line_event_read(alarm_line, &line_event);
        if (line_event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE) {
            cout << "Alarm triggered" << endl;
            // Turn LED on
            gpiod_line_set_value(led_line, 1);
			cout << "LED on" << endl;
            // Clear alarm flags
            rtcmodule.clearFlags();

			// Leave LED on for 5 seconds
			sleep(5);

			// turn LED off
			gpiod_line_set_value(led_line, 0);
			cout << "LED off" << endl;

            break;
        }
    }
	gpiod_line_release(alarm_line);
    gpiod_line_release(led_line);
    gpiod_chip_close(chip);
	rtcmodule.setSquareWaveOutput(true, 1);
	uint8_t controlRegister = rtcmodule.readRegister(0x0E);
    cout << "Control Register's value, should be 0x08 - " << hex << int(controlRegister) << endl;
	return 0;
}