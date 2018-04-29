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
    USBInterface* usb = new USBInterface(
                                Yokogawa::WT3000::USB::VID,
                                Yokogawa::WT3000::USB::PID,
                                Yokogawa::WT3000::USB::EndpointTransmit,
                                Yokogawa::WT3000::USB::EndpointReceive
                                );

    Yokogawa::WT3000::WT3000* analyzer = new Yokogawa::WT3000::WT3000(usb);
    analyzer->connect();

    for (uint8_t i=0; i<1; i++)
    {
        cout << "Urms1: " << analyzer->getNumericValues() << endl;
        this_thread::sleep_for(1s);
    }

    delete analyzer;
    delete usb;
}
