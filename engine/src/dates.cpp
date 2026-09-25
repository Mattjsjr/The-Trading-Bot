#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include "dates.h"

std::string dateDaysAgo(int daysAgo) {
    auto now = std::chrono::system_clock::now();
    auto target = now - std::chrono::hours(24 * daysAgo);

    std::time_t t = std::chrono::system_clock::to_time_t(target);
    std::tm tm = *std::gmtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}