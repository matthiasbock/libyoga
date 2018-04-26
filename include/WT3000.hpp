/**
 * @file
 * Instantiate and interact with a Yokogawa WT3000 power analyzer
 */

#ifndef WT3000_HPP
#define WT3000_HPP

#include <stdbool.h>
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

        /**
         * Convenience method to prepare the device
         * for communication
         */
        void connect();

        const string cmdGroupCommunicate = ":COMMunicate";
        const string cmdCommunicateRemote = ":REMote";

        void setRemote(bool);

        const string cmdInstrumentModel = "*IDN?";

        string getInstrumentModel();
    };
}

#endif
