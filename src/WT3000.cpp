
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
}


void WT3000::setRemote(bool enable)
{
    string s = cmdGroupCommunicate + cmdCommunicateRemote + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void WT3000::read()
{

}
