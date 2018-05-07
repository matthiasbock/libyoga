/**
 * @file
 * All methods necessary for USB communication
 */

#ifndef USBINTERFACE_HPP
#define USBINTERFACE_HPP

#include <Logging.hpp>
#include "stdint.h"
#include "iostream"
#include "string"
#include "string.h"
#include "libusb-1.0/libusb.h"

using namespace std;

class USBInterface
{
private:
    LogLevel::type loglevel = LogLevel::Debug;
    libusb_device *dev, **devs;
    libusb_device_handle *device = NULL;
    struct libusb_device_descriptor desc;
    uint8_t endpoint_send;
    uint8_t endpoint_receive;

public:
    USBInterface(uint16_t vid, uint16_t pid, uint8_t ep_out, uint8_t ep_in);
    ~USBInterface();

    /*
     * Adjust the object's loglevel to your preference
     */
    void setLogLevel(LogLevel::type);

    /**
     * Perform blocking USB transmission
     */
    void send(string& s);

    /**
     * Perform blocking USB reception (printable characters only)
     */
    string receive();

    /**
     * Perform blocking USB reception
     */
    bool receive(unsigned char* buffer, int length_max, int* length_received);
};

#endif
