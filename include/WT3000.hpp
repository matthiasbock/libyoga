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
        const string cmdInstrumentModel = "*IDN?";

        namespace Communicate
        {
            const string cmdGroup = ":COMMunicate";
            const string cmdRemote = ":REMote";
        }

        namespace Status
        {
            const string cmdGroup = ":STATus";
            const string cmdExtendedEventStatusEnable = ":EESE";
            const string cmdFilter = ":FILTer";

            namespace Filter
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

            string getInstrumentModel();

            void setExtendedEventStatusEnable(bool);

            void setStatusFilter(string number, string condition);
        };
    }
}

#endif
