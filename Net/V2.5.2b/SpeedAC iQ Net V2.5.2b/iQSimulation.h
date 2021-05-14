bool iQSimOpen
    (int handle,
    int scaleno,
    string ip_address);

bool iQSimClose
    (int handle,
    int scaleno);

bool iQSimSetWeight
    (int handle,
    int scaleno,
    float weight);

string iQSimFormatProgram
    (string function_of_t,
    float duration);

bool iQSimSetProgram
    (int handle,
    int scaleno,
    string program);

bool iQSimStartProgram
    (int handle,
    int scaleno);

bool iQSimStopProgram
    (int handle,
    int scaleno);

#include "iQSimulation.ccf"
