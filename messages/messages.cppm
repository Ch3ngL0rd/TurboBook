module;
#include <iostream>
#include <cstdint>
export module messages;

export struct SystemEvent
{
    uint8_t timestamp[6];
    char event_code;
};

export struct StockDirectory {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint8_t timestamp[6];
    char stock[8];
    char market_category;
    char financial_status_indicator;
}

export SystemEvent read_system_event(std::istream& in);
export StockDirectory read_stock_directory(std::istream& in);