#include "average_price.h"
#include "vector"
#include "nlohmann/json.hpp"

int averagePrice(const std::vector<nlohmann::json>& stockData){
    double total = 0;
    int count = 0;
    for (const auto& item : stockData){
        total += item.at("close").get<double>();
        count += 1;
    }
    return total / count;
}