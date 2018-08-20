
#include <WT3000.hpp>

using namespace std;
using namespace Yokogawa::WT3000;
using namespace Yokogawa::WT3000::GPIB;


Interface::Interface(USBInterface* usb)
{
    this->usb = usb;
}


Interface::~Interface()
{
    setRemote(false);
}


void Interface::connect()
{
    setRemote(true);
    identify();
    setExtendedEventStatusEnable(false);
    setStatusFilter("1", Status::Transition::Rise);
    setStatusFilter("2", Status::Transition::Rise);
    setStatusFilter("7", Status::Transition::Rise);
    setOverlap(false);
    setVerbose(false);
    setHeader(false);
    setNumericFormat(Numeric::Format::Float);
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
    string s = Numeric::Group + Numeric::Format::Group + ' ' + type;
    usb->send(s);
}


void Interface::setNumericFormat(Numeric::Format::enumFormats format)
{
    switch (format)
    {
        case Numeric::Format::FORMAT_FLOAT:
            setNumericFormat(Numeric::Format::Float);
            break;
        default:
//            log(LogLevel::Warning, "Invalid format value: " << format);
            break;
    }
}


bool Interface::getNumericValues(unsigned char* buffer, int length_max, int* length_received)
{
    cout << "Reading values from device..." << endl << flush;
    string s = Numeric::Group + Numeric::Value + '?';
    usb->send(s);

    bool result = usb->receive(buffer, length_max, length_received);
    return result;
}


vector<float> Interface::getNumericValuesAsFloats()
{
    vector<float> v;

    unsigned char rawData[10000];
    int length_received;
    if (!getNumericValues(rawData, sizeof(rawData), &length_received))
    {
        cerr << "Data reception failed" << endl << flush;
        return v;
    }

    if (length_received < 6)
    {
        cerr << "Data stream ended prematurely" << endl << flush;
        return v;
    }

    if (rawData[0] != '#')
    {
        cerr << "Illegal character at position 0" << endl << flush;
        return v;
    }

    if (rawData[1] != '4')
    {
        cerr << "Illegal character at position 1" << endl << flush;
        return v;
    }

    // The payload data length is stored in the form of four ASCII-encoded bytes after the '#4' preamble.
    char length_str[5];
    for (uint8_t i=0; i<4; i++)
    {
        length_str[i] = rawData[2+i];
    }
    length_str[4] = 0;
    uint32_t length_announced = atoi(length_str);

    // 6 characters are for the preamble
    uint32_t length_payload = length_received - 6;

    // minus 1, if a line-wrap was appended
    if (rawData[length_received-1] == 0x0a)
        length_payload--;

    if (length_payload != length_announced)
    {
        cerr << "Data length mismatch: Expected " << length_announced << " bytes of payload, got " << length_payload << endl << flush;
        return v;
    }

    cout << "Got " << length_payload << " bytes of data." << endl << flush;
    cout << "Assuming format: float" << endl << flush;

    uint8_t* b = (uint8_t*) (rawData)+6;
    for (uint16_t i=6; i<length_payload/4; i++)
    {
        union
        {
            float f;
            uint8_t b[4];
        } u;
        u.b[3] = *(b++);
        u.b[2] = *(b++);
        u.b[1] = *(b++);
        u.b[0] = *(b++);

        printf("%0.05f ", u.f);
    }
    cout << endl << flush;

    return v;
}
