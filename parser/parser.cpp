module;
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <format>
#include <string.h>
module parser;

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
            auto se = read_system_event(in);
            std::cout << std::format("System event: {}\n", se.event_code);
        }
        else if (message_type == 'R')
        {
            auto sd = read_stock_directory(in);
            std::string stock_trimmed(sd.stock, strnlen(sd.stock, 8)); // Trim space padding
            std::cout << stock_trimmed << '\t';
        }
        else
        {
            in.ignore(message_length - 1);
        }

        ++message_count;
    }
    std::cout << std::format("There were {} messages.\n", message_count);
}