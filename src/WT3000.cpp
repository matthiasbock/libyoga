
#include <WT3000.hpp>

using namespace Yokogawa::WT3000;


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
    setStatusFilter("1", Status::Filter::Rise);
    setStatusFilter("2", Status::Filter::Rise);
    setStatusFilter("7", Status::Filter::Rise);

}


void WT3000::setRemote(bool enable)
{
    string s = Communicate::cmdGroup + Communicate::cmdRemote + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


string WT3000::getInstrumentModel()
{
    string s = cmdInstrumentModel;
    usb->send(s);
    return usb->receive();
}


void WT3000::setExtendedEventStatusEnable(bool enable)
{
    string s = Status::cmdGroup + Status::cmdExtendedEventStatusEnable + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void WT3000::setStatusFilter(string number, string condition)
{
    string s = Status::cmdGroup + Status::cmdFilter + number + ' ' + condition;
    usb->send(s);
}
