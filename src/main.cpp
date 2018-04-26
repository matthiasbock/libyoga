/**
 * @file
 * Connects to a Yokogawa WT3000 power analyzer via USB
 * and reads the current measurement values
 */

#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <thread>
#include <USBInterface.hpp>
#include <WT3000.hpp>


using namespace std;
using namespace std::chrono_literals;


int main()
{
    USBInterface* usb = new USBInterface();
//    usb.select...

    Yokogawa::WT3000* analyzer = new Yokogawa::WT3000(usb);

    for (uint8_t i=0; i<3; i++)
    {
        analyzer->read();
        this_thread::sleep_for(1s);
    }

    delete analyzer;
    delete usb;
}
