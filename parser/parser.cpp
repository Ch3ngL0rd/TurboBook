#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <format>

void parse(std::istream &in, std::ostream &out)
{
    while (in)
    {
        char len_bytes[2];
        in.read(len_bytes, 2);
        if (in.gcount() != 2)
        {
            std::cerr << std::format("Error reading message length at position: {}\n",
                                     static_cast<std::streamoff>(in.tellg()));
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

        out << "Message type: " << message_type << '\n';
        in.ignore(message_length - 1);
    }
}