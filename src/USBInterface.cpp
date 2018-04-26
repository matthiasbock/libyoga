
#include <USBInterface.hpp>


void USBInterface::send(string& s)
{
    /*
     * Data from host to device:
     *  URB_BULK via USB endpoint 0x01
     */
    cout << s << endl;
}


string USBInterface::receive()
{
    /*
     * Data from device to host:
     *  URB_BULK via USB endpoint 0x83
     */
    string s = "DUMMY";
    return s;
}
