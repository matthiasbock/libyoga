
#include <WT3000.hpp>

using namespace Yokogawa::WT3000;
using namespace Yokogawa::WT3000::GPIB;


Interface::Interface(USBInterface* usb)
{
    this->usb = usb;
}


Interface::~Interface() {}


void Interface::connect()
{
    this->setRemote(true);
    cout << identify() << endl;
    setExtendedEventStatusEnable(false);
    setStatusFilter("1", Status::Transition::Rise);
    setStatusFilter("2", Status::Transition::Rise);
    setStatusFilter("7", Status::Transition::Rise);
    setOverlap(false);
    setVerbose(false);
    setHeader(false);
    setNumericFormat(Numeric::Type::Float);
}


void Interface::setRemote(bool enable)
{
    string s = Communicate::Group + Communicate::Remote + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void Interface::clearStatus()
{
    string s = ClearStatus;
    usb->send(s);
}


string Interface::identify()
{
    string s = Identify;
    usb->send(s);
    return usb->receive();
}


void Interface::setExtendedEventStatusEnable(bool enable)
{
    string s = Status::Group + Status::ExtendedEventStatusEnable + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void Interface::setStatusFilter(string number, string condition)
{
    string s = Status::Group + Status::Filter + number + ' ' + condition;
    usb->send(s);
}


void Interface::setOverlap(bool enable)
{
    string s = Communicate::Group + Communicate::Overlap + ' ' + (enable ? "96" : "0");
    usb->send(s);
}


void Interface::setVerbose(bool enable)
{
    string s = Communicate::Group + Communicate::Verbose + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void Interface::setHeader(bool enable)
{
    string s = Communicate::Group + Communicate::Header + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


string Interface::getInputModule(string number)
{
    string s = Input::Group + Input::Module + ' ' + number;
    usb->send(s);
    return usb->receive();
}


void Interface::setNumericFormat(string type)
{
    string s = Numeric::Group + Numeric::Format + ' ' + type;
    usb->send(s);
}


string Interface::getNumericValues()
{
    string s = Numeric::Group + Numeric::Value + '?';
    usb->send(s);
    return usb->receive();
}
