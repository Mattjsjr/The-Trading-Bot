#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "Trading bot engine\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Line two";
    return 0;
}