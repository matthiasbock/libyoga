/**
 * @file
 * Connects to a Yokogawa WT3000 power analyzer via USB
 * and reads the current measurement values
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <thread>
#include <USBInterface.hpp>
#include <WT3000.hpp>
#include <vector>


using namespace std;
using namespace std::chrono_literals;


USBInterface* usb;
Yokogawa::WT3000::Interface* analyzer;

int main()
{
    usb = new USBInterface();
    usb->open(
            Yokogawa::WT3000::USB::VID,
            Yokogawa::WT3000::USB::PID,
            Yokogawa::WT3000::USB::EndpointTransmit,
            Yokogawa::WT3000::USB::EndpointReceive
            );
    usb->setLogLevel(LogLevel::None);

    if (!usb->isOpen())
    {
        return -1;
    }

    analyzer = new Yokogawa::WT3000::Interface();
    analyzer->setUSBInterface(usb);
    analyzer->connect();
    analyzer->setLogLevel(LogLevel::None);
    analyzer->connect();

    analyzer->setNumericFormat(Yokogawa::WT3000::GPIB::Numeric::Format::Float);

    while (true)
    {
        this_thread::sleep_for(0.25s);
        vector<float> values = analyzer->getNumericValuesAsFloats();

        // For 1-2 seconds millions of Volt are reported, when turning on the high voltage supply.
        if ((values.at(0) < -1500.0) || (values.at(0) > 1500.0))
        {
            // Measurement values are not plausible, that's probably an error, discard this measurement
            continue;
        }

        // For 1-2 seconds millions of Ampere are reported, when turning on the high current sink.
        if ((values.at(4) < -1.0) || (values.at(4) > 100.0))
        {
            // Measurement values are not plausible, that's probably an error, discard this measurement
            continue;
        }

        printf("Urms1 = %2.5f V, ", values.at(0));
        printf("Idc1 = %2.5f A, ", values.at(1));
        printf("P1 = %2.5f W, ", values.at(2));
        printf("Urms2 = %2.5f V, ", values.at(3));
        printf("Irms2 = %2.5f A, ", values.at(4));
        printf("P2 = %2.5f W \n", values.at(5));
        cout << flush;
    }
}
