
#include <WT3000.hpp>

using namespace Yokogawa;


WT3000::WT3000(USBInterface* usb)
{
    this->usb = usb;
}


WT3000::~WT3000() {}


void WT3000::connect()
{
    this->setRemote(true);
    cout << getInstrumentModel() << endl;
    setExtendedEventStatusEnable(false);
}


void WT3000::setRemote(bool enable)
{
    string s = cmdGroupCommunicate + cmdCommunicateRemote + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


string WT3000::getInstrumentModel()
{
    usb->send(cmdInstrumentModel);
    return usb->receive();
}


void WT3000::setExtendedEventStatusEnable(bool enable)
{
    string s = cmdGroupStatus + cmdStatusExtendedEventStatusEnable + ' ' + (enable ? '1' : '0');
    usb->send(s);
}
