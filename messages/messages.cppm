module;
#include <iostream>
#include <cstdint>
export module messages;

export struct SystemEvent
{
    uint8_t timestamp[6];
    char event_code;
};

export struct StockDirectory
{
    // char message_type;                         // offset 0
    uint16_t stock_locate;                     // offset 1..2
    uint16_t tracking_number;                  // offset 3..4
    uint8_t  timestamp[6];                     // offset 5..10  (6 bytes in big-endian)
    char     stock[8];                         // offset 11..18 (ASCII, space-padded)
    char     market_category;                  // offset 19
    char     financial_status_indicator;       // offset 20
    uint32_t round_lot_size;                   // offset 21..24 (big-endian)
    char     round_lots_only;                  // offset 25
    char     issue_classification;             // offset 26
    char     issue_subtype[2];                 // offset 27..28
    char     authenticity;                     // offset 29
    char     short_sale_threshold_indicator;   // offset 30
    char     ipo_flag;                         // offset 31
    char     luld_reference_price_tier;        // offset 32
    char     etp_flag;                         // offset 33
    uint32_t etp_leverage_factor;              // offset 34..37 (big-endian)
    char     inverse_indicator;                // offset 38
};


export SystemEvent read_system_event(std::istream& in);
export StockDirectory read_stock_directory(std::istream& in);