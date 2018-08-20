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
    USBInterface usb(
                    Yokogawa::WT3000::USB::VID,
                    Yokogawa::WT3000::USB::PID,
                    Yokogawa::WT3000::USB::EndpointTransmit,
                    Yokogawa::WT3000::USB::EndpointReceive
                    );
    usb.setLogLevel(LogLevel::Debug);

    if (!usb.isOpen())
    {
        return -1;
    }

    Yokogawa::WT3000::Interface analyzer(&usb);
    analyzer.connect();

    analyzer.setNumericFormat(Yokogawa::WT3000::GPIB::Numeric::Format::Float);

    for (uint8_t i=0; i<1; i++)
    {
        analyzer.getNumericValuesAsFloats();
        this_thread::sleep_for(1s);
    }
}
