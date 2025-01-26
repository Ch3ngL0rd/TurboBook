# Day 1 25/01/25
- Initialised project. Added basic readme.md
- Scoped out project goals and how to measure progress
- North Star Metric: Orders Processed Per Second (OPS) with p99 Latency < xμs
- Correctness: Verification of orderbook against NASDAQ closing auction data
- Goal: Produce measurable results of technical learnings. Have fun.
- First step is download ITCH data.
- [command] tail -f wget-log - monitor a file in realtime - pretty cool

# Day 2 26/01/25
- ITCH50 is a data feed used for stock market data
    - gives full depth of the market, allowing for complete order book reconstruction
- Add (A), Modify (U), Cancel (D), Execute (E/C), Replace (R)
hexdump -C ./data/raw/01302019.NASDAQ_ITCH50 | head -n 1
- Protocol specified: https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NQTVITCHSpecification.pdf
- big endian - signficant byte first
- parsing is difficult. reading the protocol and understanding it should've come first.
- Errors parsing since there is a MoldUDPHeader protocol header...
- Reading directly from std::cin may cause issues.
- Not reading in binary mode may create translation corruption.
- [learning] gcount: returns the number of characters read by most recent unformatted input operation
- Using C++20 features: format
- [learning] static_cast<std::streamoff>(in.tellg()): required since in.tellg() returns std::streampos
    - not formattable by default
    - static_cast<std::streamoff> converts it byte offset