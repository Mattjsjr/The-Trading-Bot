#include <nlohmann/json.hpp>
#include "alpaca_client.cpp"
#include "get_stock_data.h"

std::vector<nlohmann::json> fetchStockData(const std::optional<std::string>& fmp_secret, const std::string& ticker, const std::string& start_date, const std::string& end_date)
{
    if (!fmp_secret) {
        throw std::runtime_error("Missing FMP_API_KEY");
    }

    fmp::Config config;
    config.api_key = *fmp_secret;
    config.start_date = start_date;
    config.end_date = end_date;
    config.ticker = ticker;

    fmp::Client fmp_client(config);
    return fmp_client.current();
}