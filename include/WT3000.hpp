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
        };
    }
}

#endif
