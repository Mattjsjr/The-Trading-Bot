#include <iostream>
#include <thread>
#include <chrono>
#include "dotenv.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "alpaca_client.cpp"

int main() {

    std::optional<std::string> key = getDotEnvVariable("ALPACA_API_KEY");
    std::optional<std::string> secret = getDotEnvVariable("ALPACA_API_SECRET");


    return 0;
}