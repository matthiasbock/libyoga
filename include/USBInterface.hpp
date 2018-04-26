/**
 * @file
 * All methods necessary for USB communication
 */

#ifndef USBINTERFACE_HPP
#define USBINTERFACE_HPP

#include <iostream>
#include <stddef.h>

using namespace std;


class USBInterface
{
public:
    USBInterface() {};
    ~USBInterface() {};

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
