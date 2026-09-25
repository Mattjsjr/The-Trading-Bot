#include <iostream>
#include <thread>
#include <chrono>
#include "dotenv.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "alpaca_client.cpp"
#include "dates.h"
#include "average_price.h"
#include <queue>
#include <utility>
#include "stock_tickers.h"
#include "get_stock_data.h"

int main() {

    std::optional<std::string> key = getDotEnvVariable("ALPACA_API_KEY");
    std::optional<std::string> secret = getDotEnvVariable("ALPACA_API_SECRET");
    std::optional<std::string> fmp_secret = getDotEnvVariable("FMP_API");
    std::string today = dateDaysAgo(0);
    std::string fiftydays = dateDaysAgo(75);
    std::string twentydays = dateDaysAgo(26);

    try{
        fmp::Config config;
        std::priority_queue<std::pair<double, std::string>> top_stock;
        for (std::string ticker : stock_tickers ){

            auto stock20 = fetchStockData(fmp_secret, ticker, twentydays, today);
            auto stock50 = fetchStockData(fmp_secret, ticker, fiftydays, today);
            double average20 = averagePrice(stock20);
            double average50 = averagePrice(stock50);
            double bounce = average20 - average50;

            if (bounce > 0){
                top_stock.push({bounce, ticker});
            }
            
        }
        if (top_stock.empty()){
            std::cout << "No good stocks\n";
        } else {
            auto best = top_stock.top();
            std::cout << best.second << ": " << best.first << "\n";
        }

    } catch (const http::ApiError& e) {
        std::cerr << "API error: " << e.what() << "\n";
        return 1;
    } catch (const nlohmann::json::exception&e){
        std::cerr << "Unexpected response shape: " << e.what() << "\n";
        return 1;
    }

    return 0;
}