
#include <USBInterface.hpp>


void USBInterface::send(string& s)
{
    /*
     * Data from host to device:
     *  URB_BULK via USB endpoint 1
     */
    cout << s << endl;
}


string USBInterface::receive()
{
    string s = "DUMMY";
    return s;
}
