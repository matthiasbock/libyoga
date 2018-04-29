/**
 * @file
 * All methods necessary for USB communication
 */

#ifndef USBINTERFACE_HPP
#define USBINTERFACE_HPP

#include "stdint.h"
#include "stddef.h"
#include <iostream>
#include "string"
#include "libusb-1.0/libusb.h"

using namespace std;


class USBInterface
{
private:
    libusb_device *dev, **devs;
    libusb_device_handle *device = NULL;
    struct libusb_device_descriptor desc;
    uint8_t endpoint_send;
    uint8_t endpoint_receive;

public:
    USBInterface(uint16_t vid, uint16_t pid, uint8_t ep_out, uint8_t ep_in);
    ~USBInterface();

    /**
     * Perform blocking USB transmission
     */
    void send(string& s);

    /**
     * Perform blocking USB reception
     */
    string receive();
};

#endif
