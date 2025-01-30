module;
#include <iostream>
#include <cstdint>
module messages;

SystemEvent read_system_event(std::istream &in)
{
    SystemEvent s;
    in.ignore(4);

    in.read(reinterpret_cast<char*>(s.timestamp), 6);
    
    s.event_code = in.get();

    return s;
}

StockDirectory read_stock_directory(std::istream& in)
{
    StockDirectory sd;
    char buffer[4];

    in.read(buffer, 2);
    sd.stock_locate =
        (static_cast<uint8_t>(buffer[0]) << 8) |
         static_cast<uint8_t>(buffer[1]);

    in.read(buffer, 2);
    sd.tracking_number =
        (static_cast<uint8_t>(buffer[0]) << 8) |
         static_cast<uint8_t>(buffer[1]);

    in.read(reinterpret_cast<char*>(sd.timestamp), 6);

    in.read(sd.stock, 8);

    in.read(&sd.market_category, 1);

    in.read(&sd.financial_status_indicator, 1);

    in.read(buffer, 4);
    sd.round_lot_size =
       (static_cast<uint8_t>(buffer[0]) << 24) |
       (static_cast<uint8_t>(buffer[1]) << 16) |
       (static_cast<uint8_t>(buffer[2]) <<  8) |
        static_cast<uint8_t>(buffer[3]);

    in.read(&sd.round_lots_only, 1);

    in.read(&sd.issue_classification, 1);

    in.read(sd.issue_subtype, 2);

    in.read(&sd.authenticity, 1);

    in.read(&sd.short_sale_threshold_indicator, 1);

    in.read(&sd.ipo_flag, 1);

    in.read(&sd.luld_reference_price_tier, 1);

    in.read(&sd.etp_flag, 1);

    in.read(buffer, 4);
    sd.etp_leverage_factor =
       (static_cast<uint8_t>(buffer[0]) << 24) |
       (static_cast<uint8_t>(buffer[1]) << 16) |
       (static_cast<uint8_t>(buffer[2]) <<  8) |
        static_cast<uint8_t>(buffer[3]);

    in.read(&sd.inverse_indicator, 1);

    return sd;
}