
#ifndef LOGFILE_HPP
#define LOGFILE_HPP

#include <string>
#include <fstream>


using namespace std;


class Logfile
{
private:
    ofstream logfile;

public:
    Logfile() {};
    ~Logfile()
    {
        if (logfile.is_open())
        {
            logfile.close();
        }
    }


    void open(string filename)
    {
        logfile.open(filename);
    }


    void writeln(string msg)
    {
        logfile << msg << endl << flush;
    }
};


#endif
