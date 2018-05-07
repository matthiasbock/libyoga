
#ifndef LOGLEVEL_HPP
#define LOGLEVEL_HPP

#include <iostream>

using namespace std;

namespace LogLevel
{
    typedef enum
    {
        None = 0,
        Error = 1,
        Warning = 2,
        Info = 3,
        Debug = 4,
    } type;
}

#define log(level, msg)     if (loglevel >= level) { cout << msg << endl << flush; }

#endif
