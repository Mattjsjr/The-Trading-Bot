#include "vector"
#include <nlohmann/json.hpp>

std::vector<nlohmann::json> fetchStockData(const std::optional<std::string>& fmp_secret, const std::string& ticker, const std::string& start_date, const std::string& end_date);
