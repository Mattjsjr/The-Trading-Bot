#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include "alpaca_client.h"

namespace alpaca {
    using json = nlohmann::json;

    struct Config {
        std:: string base_url = "https://financialmodelingprep.com";
        std::chrono::milliseconds timeout{5000};
        std::string api_key = "";
        std::string api_secret = "";
    };

    struct SPConstituent {
        std:: string symbol;
        std:: string name;
    };

    class ApiError : std::runtime_error {
        public: 
            ApiError(long status, const std::string& errorMessage)
            : runtime_error("HTTP " + std::to_string(status) + ": " + errorMessage), 
            status_(status){}

            long status() const noexcept {return status_;}

        private:
        long status_;
    };

    class Client {
        public:
            explicit Client(Config cfg = {}) : cfg_(std::move(cfg)) {}

            SPConstituent current(std::string symbol, std::string name) const {
                const cpr::Response res = cpr::Get(
                    cpr::Url{cfg_.base_url},
                    cpr::Header{
                        {"APCA-API-KEY-ID", cfg_.api_key},
                        {"APCA-API-SECRET-KEY", cfg_.api_secret}},
                    cpr::Timeout{static_cast<int32_t>(cfg_.timeout.count())});

                if (res.error){
                    throw ApiError(0, "transport error: " + res.error.message);
                }
                if (res.status_code != 200){
                    throw ApiError(res.status_code, res.text);
                }

                const json body = json::parse(res.text);
                return {"https", "apl"};
            }

        private: 
            Config cfg_;
    };

};