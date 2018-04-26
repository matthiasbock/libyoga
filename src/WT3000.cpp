
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


void WT3000::setRemote(bool enable)
{
    string s = Communicate::Group + Communicate::Remote + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void WT3000::clearStatus()
{
    string s = ClearStatus;
    usb->send(s);
}


string WT3000::identify()
{
    string s = Identify;
    usb->send(s);
    return usb->receive();
}


void WT3000::setExtendedEventStatusEnable(bool enable)
{
    string s = Status::Group + Status::ExtendedEventStatusEnable + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void WT3000::setStatusFilter(string number, string condition)
{
    string s = Status::Group + Status::Filter + number + ' ' + condition;
    usb->send(s);
}


void WT3000::setOverlap(bool enable)
{
    string s = Communicate::Group + Communicate::Overlap + ' ' + (enable ? "96" : "0");
    usb->send(s);
}


void WT3000::setVerbose(bool enable)
{
    string s = Communicate::Group + Communicate::Verbose + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


void WT3000::setHeader(bool enable)
{
    string s = Communicate::Group + Communicate::Header + ' ' + (enable ? '1' : '0');
    usb->send(s);
}


string WT3000::getInputModule(string number)
{
    string s = Input::Group + Input::Module + ' ' + number;
    usb->send(s);
    return usb->receive();
}


void WT3000::setNumericFormat(string type)
{
    string s = Numeric::Group + Numeric::Format + ' ' + type;
    usb->send(s);
}


string WT3000::getNumericValues()
{
    string s = Numeric::Group + Numeric::Value + '?';
    usb->send(s);
    return usb->receive();
}
