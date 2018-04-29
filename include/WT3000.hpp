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
    namespace WT3000
    {
        namespace USB
        {
            /** Yokogawa USB Vendor ID */
            const uint16_t VID = 0x0b21;

            /** Yokogawa WT3000 USB Product ID */
            const uint16_t PID = 0x0025;

            /**
             * Data from host to device:
             *  URB_BULK via USB endpoint 0x01
             */
            const uint8_t EndpointTransmit = 0x01;

            /**
             * Data from device to host:
             *  URB_BULK via USB endpoint 0x83
             */
            const uint8_t EndpointReceive = 0x83;
        }


        const string ClearStatus = "*CLS";
        const string Identify = "*IDN?";

        namespace Communicate
        {
            const string Group = ":COMMunicate";
            const string Header = ":HEADer";
            const string Overlap = ":OVERlap";
            const string Remote = ":REMote";
            const string Verbose = ":VERBose";
        }

        namespace Input
        {
            const string Group = ":INPut";
            const string Module = ":MODUle";
            const string Voltage = ":VOLTage";
            const string Current = ":CURRent";
        }

        namespace Numeric
        {
            const string Group = ":NUMeric";
            const string Format = ":FORMat";

            namespace Type
            {
                const string ASCII = "ASCii";
                const string Float = "FLOat";
            }

            const string Value = ":VALue";
        }

        namespace Status
        {
            const string Group = ":STATus";
            const string ExtendedEventStatusEnable = ":EESE";
            const string Filter = ":FILTer";

            namespace Transition
            {
                const string Rise = "RISE";
                const string Fall = "FALL";
                const string Both = "BOTH";
                const string Never = "NEVER";
            }
        }

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

            void setRemote(bool);

            /**
             * Queries the instrument model
             */
            string identify();

            /**
             * Clears the standard event register, extended event register, and error queue
             */
            void clearStatus();

            void setExtendedEventStatusEnable(bool);

            void setStatusFilter(string number, string condition);

            /**
             * Sets the commands that will operate as overlap commands
             */
            void setOverlap(bool);

            /**
             * Sets whether to return the response to a query using full spelling
             */
            void setVerbose(bool);

            /**
             * Sets whether to add a header to the response to a query
             */
            void setHeader(bool);

            /**
             * Queries the input element type
             */
            string getInputModule(string number);

            void setNumericFormat(string type);

            /**
             * Queries numeric data (measurement results) from the device
             */
            string getNumericValues();
        };
    }
}

#endif
