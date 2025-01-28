module;
#include <iostream>
#include <cstdint>
export module messages;

export struct SystemEvent
{
    uint8_t timestamp[6];
    char event_code;
};

export SystemEvent read_event_code(std::istream& in);