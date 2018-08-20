
#include <USBInterface.hpp>
#include <stdio.h>


USBInterface::USBInterface(uint16_t vid, uint16_t pid, uint8_t ep_out, uint8_t ep_in)
{
    opened = false;

    int rc = libusb_init(NULL);
    if (rc < 0)
    {
        log(LogLevel::Error, "Error initializing libusb");
        return;
    }

    // Set debug output level to max
    libusb_set_debug(NULL, 3);

    device = libusb_open_device_with_vid_pid(NULL, (uint16_t)vid, (uint16_t)pid);
    if (device == NULL)
    {
        log(LogLevel::Error, "Opening USB device failed.");
        return;
    }

    libusb_set_auto_detach_kernel_driver(device, 1);
    int status = libusb_claim_interface(device, 0);
    if (status != LIBUSB_SUCCESS)
    {
        libusb_close(device);
        log(LogLevel::Error, "Claiming the USB interface failed with error " << libusb_error_name(status));
        return;
    }

    log(LogLevel::Info, "Successfully opened and claimed USB device.");

    endpoint_send = ep_out;
    endpoint_receive = ep_in;
    opened = true;
}


USBInterface::~USBInterface()
{
    if (isOpen())
    {
        libusb_release_interface(device, 0);
        libusb_close(device);
        libusb_exit(NULL);
    }
}


void USBInterface::setLogLevel(LogLevel::type level)
{
    loglevel = level;
}


void USBInterface::send(string& s)
{
    unsigned char* buffer = (unsigned char*) s.c_str();
    int length = s.length();
    int actual_length;
    const unsigned int timeout_ms = 1000;

    log(LogLevel::Debug, "Sending: " << s);
    int status = libusb_bulk_transfer(
                    device,
                    endpoint_send,
                    buffer,
                    length,
                    &actual_length,
                    timeout_ms
                    );

    if (status != 0)
    {
        log(LogLevel::Error, "Send failed with error " << libusb_error_name(status));
        return;
    }
}


string USBInterface::receive()
{
    unsigned char buffer[1024];
    int length = sizeof(buffer);
    int length_received;
    const unsigned int timeout_ms = 1000;

    int status = libusb_bulk_transfer(
                    device,
                    endpoint_receive,
                    buffer,
                    length,
                    &length_received,
                    timeout_ms
                    );

    if (status != 0)
    {
        log(LogLevel::Error, "Receive failed with error " << libusb_error_name(status));
        return "";
    }

    string s = string((const char*) buffer);

    // Termiante string earlier, if last character is line-wrap
    if (buffer[length_received-1] == 0x0a)
        buffer[length_received-1] = 0;
    log(LogLevel::Debug, "Received " << length_received << " byte(s): " << buffer);

    return s;
}


bool USBInterface::receive(unsigned char* buffer, int length_max, int* length_received)
{
    const unsigned int timeout_ms = 1000;

    int status = libusb_bulk_transfer(
                    device,
                    endpoint_receive,
                    buffer,
                    length_max,
                    length_received,
                    timeout_ms
                    );

    if (status != 0)
    {
        log(LogLevel::Error, "Receive failed with error " << libusb_error_name(status));
        return false;
    }

    log(LogLevel::Debug, "Received " << *length_received << " byte(s)");

    return true;
}
