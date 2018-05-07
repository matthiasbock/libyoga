
#include <USBInterface.hpp>
#include <stdio.h>


USBInterface::USBInterface(uint16_t vid, uint16_t pid, uint8_t ep_out, uint8_t ep_in)
{
    int rc = libusb_init(NULL);
    if (rc < 0)
    {
        cerr << "Error initializing libusb" << endl << flush;
        return;
    }

    // Set debug output level to max
    libusb_set_debug(NULL, 3);

    device = libusb_open_device_with_vid_pid(NULL, (uint16_t)vid, (uint16_t)pid);
    if (device == NULL)
    {
        printf("Opening USB device failed.\n");
        return;
    }

    libusb_set_auto_detach_kernel_driver(device, 1);
    int status = libusb_claim_interface(device, 0);
    if (status != LIBUSB_SUCCESS)
    {
        libusb_close(device);
        printf("Claiming the USB interface failed with error %s.\n", libusb_error_name(status));
        return;
    }

    cout << "Successfully opened and claimed USB device." << endl << flush;

    endpoint_send = ep_out;
    endpoint_receive = ep_in;
}


USBInterface::~USBInterface()
{
    libusb_release_interface(device, 0);
    libusb_close(device);
    libusb_exit(NULL);
}


void USBInterface::send(string& s)
{
    unsigned char* buffer = (unsigned char*) s.c_str();
    int length = s.length();
    int actual_length;
    const static unsigned int timeout_ms = 1000;

    cout << "Sending..." << endl << flush;
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
        printf("Send failed with error %s.\n", libusb_error_name(status));
        return;
    }
}


string USBInterface::receive()
{
    unsigned char buffer[100];
    int length = sizeof(buffer);
    int length_received;
    const static unsigned int timeout_ms = 1000;

    cout << "Receiving..." << endl << flush;
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
        printf("Receive failed with error %s.\n", libusb_error_name(status));
        return "";
    }

    return string((const char*) buffer);
}
