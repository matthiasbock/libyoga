/**
 * @file
 * Instantiate and interact with a Yokogawa WT3000 power analyzer
 */

#ifndef WT3000_HPP
#define WT3000_HPP


#include <USBInterface.hpp>

using namespace std;


namespace Yokogawa
{
    class WT3000
    {
    private:
        USBInterface* usb;

    public:
        WT3000(USBInterface*);
        ~WT3000();

        void read();
    };
}

#endif
