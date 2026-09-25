# The Trading Bot

A small C++ command-line tool that runs a moving-average crossover check over the 100 largest stocks in the S&P 500 and tells you which one to buy.

## How it works

For each of the top 100 S&P 500 tickers (listed in `engine/src/stock_tickers.cpp`), the engine:

1. Pulls daily close prices from the [Financial Modeling Prep](https://financialmodelingprep.com/) historical price API.
2. Calculates two simple moving averages of the close price:
   - **20-day average** (short term, using the last ~26 calendar days)
   - **50-day average** (long term, using the last ~75 calendar days)
3. Subtracts the 50-day average from the 20-day average.

A positive difference means the short-term average is above the long-term one, which is a bullish crossover signal. The stock with the largest positive difference is printed as the one to buy:

```
NVDA: 12.34
```

If no stock has its 20-day average above its 50-day average, it prints `No good stocks`.

## Project layout

```
engine/
├── CMakeLists.txt
├── vcpkg.json              # dependencies: cpr, nlohmann-json, catch2
└── src/
    ├── main.cpp            # loops over tickers, compares averages, prints the pick
    ├── stock_tickers.cpp   # the top 100 S&P 500 tickers
    ├── get_stock_data.cpp  # fetches price history for one ticker
    ├── alpaca_client.cpp   # HTTP clients (FMP and Alpaca)
    ├── average_price.cpp   # averages the close prices
    ├── dates.cpp           # builds YYYY-MM-DD dates N days ago
    └── dotenv.cpp          # reads keys from a .env file
```

## Requirements

- A C++20 compiler
- CMake 3.20 or newer
- [vcpkg](https://vcpkg.io/) for dependencies
- A Financial Modeling Prep API key

## Setup

Create a `.env` file in the directory you run the program from:

```
FMP_API=your_fmp_api_key
ALPACA_API_KEY=your_alpaca_key
ALPACA_API_SECRET=your_alpaca_secret
```

Only `FMP_API` is needed right now. The Alpaca keys are read but not used yet. `.env` files are ignored by git.

## Build and run

```sh
cd engine
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
./build/engine
```

A run makes two API requests per ticker (200 in total), so it can take a while and uses up API quota.

## Disclaimer

This is a hobby project and not financial advice. A moving-average crossover is a simple signal and should not be the only thing you base a trade on.
