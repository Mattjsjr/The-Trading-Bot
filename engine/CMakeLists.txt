cmake_minimum_required(VERSION 3.20)
project(the_trading_bot LANGUAGES CXX)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(engine src/main.cpp)
target_include_directories(engine PRIVATE include) 
target_link_libraries(engine PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
