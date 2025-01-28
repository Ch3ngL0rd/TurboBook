#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <format>

import messages;

void parse(std::istream &in, std::ostream &out)
{
    char len_bytes[2];
    auto message_count = 0;
    while (true)
    {
        // Get global position
        auto position = in.tellg();

        in.read(len_bytes, 2);
        if (in.eof() && in.gcount() == 0)
        {
            std::cerr << "EOF reached\n";
            break;
        }
        if (in.gcount() != 2)
        {
            std::cerr << std::format("Error reading message length at position: {}\n",
                                     static_cast<std::streamoff>(position));
            return;
        }

        // Read by bit shifting 2 bytes into a uint16
        uint16_t message_length = (static_cast<uint8_t>(len_bytes[0]) << 8 | static_cast<uint8_t>(len_bytes[1]));

        char message_type;
        in.get(message_type);
        if (in.gcount() != 1)
        {
            std::cerr << std::format("Error reading message type at position: {}\n",
                                     static_cast<std::streamoff>(in.tellg()));
            return;
        }

        if (message_type == 'S')
        {
            auto se = read_event_code(in);
            std::cout << std::format("System event: {}\n", se.event_code);
        }
        else
        {
            in.ignore(message_length - 1);
        }

        ++message_count;
    }
    std::cout << std::format("There were {} messages.\n", message_count);
}