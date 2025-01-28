module;
#include <iostream>
module messages;

SystemEvent read_event_code(std::istream &in)
{
    SystemEvent s;
    in.ignore(4);

    in.read(reinterpret_cast<char*>(s.timestamp), 6);
    
    s.event_code = in.get();

    return s;
}