#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <cstdlib>

using namespace std;

int main() {
    int inputPin = 27;
    int outputPin = 17;

    // 1- Write GPIO numbers to sys/class/gpio/export
    {
        ofstream exportFile("/sys/class/gpio/export");
        exportFile << inputPin;
        exportFile.close();
    }

    usleep(100000);

    {
        ofstream exportFile("/sys/class/gpio/export");
        exportFile << outputPin;
        exportFile.close();
    }
    usleep(100000);

    // Set GPIO pins as input and outputs

    {
        ofstream direction("/sys/class/gpio/gpio" + to_string(inputPin) + "/direction");
        direction << "in";
        direction.close();  // Added missing semicolon
    }
    usleep(100000);

    {
        ofstream direction("/sys/class/gpio/gpio" + to_string(outputPin) + "/direction");
        direction << "out";
        direction.close();
    }
    usleep(100000);

    // Set input GPIO to detect falling edge of sqw/int
    {
        ofstream edge("/sys/class/gpio/gpio" + to_string(inputPin) + "/edge");
        edge << "falling";
        edge.close();
    }

    // Make sure LED is off

    {
        ofstream value("/sys/class/gpio/gpio" + to_string(outputPin) + "/value");
        value << "0";
        value.close();
    }

    // Open the value file so input pin can monitor

    string path = "/sys/class/gpio/gpio" + to_string(inputPin) + "/value";
    int fd = open(path.c_str(), O_RDONLY);

    // Set up poll structure
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLPRI | POLLERR;
    char buffer[64];


    // clear previous interrupts
    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, sizeof(buffer));

    cout << "Monitoring" << endl;
    
    while (true) {
        int pollres = poll(&pfd, 1, 10000); 
        if (pollres > 0) {
            lseek(fd, 0, SEEK_SET);
            int length = read(fd, buffer, sizeof(buffer) - 1);
            buffer[length] = '\0';
            int value = atoi(buffer);
            
            
            if (value == 0) {
                cout << "Interrupt detected" << endl;
                // turn LED on
                {
                    ofstream out("/sys/class/gpio/gpio" + to_string(outputPin) + "/value");
                    out << "1";
                    out.close();

                }
                usleep(1000000); // 
                // Turn LED off
                {
                    ofstream out("/sys/class/gpio/gpio" + to_string(outputPin) + "/value");
                    out << "0";
                    out.close();
                }
            }
        } else if (pollres == 0) {

            cout << "Poll timeout" << endl;
        } 
    }

    close(fd);
    return 0;
}
