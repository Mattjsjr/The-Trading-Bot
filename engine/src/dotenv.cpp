#include <fstream>
#include <iostream>
#include <string>
#include <optional>
#include "dotenv.h"

std::optional<std::string> getDotEnvVariable(const std::string &variable){
    std::ifstream file(".env");
    if (!file.is_open()){
        std::cerr << "Could not load env variables\n";
        return "";
    }

    std::string line = "";
    std::string value = "";

    while(std::getline(file, line)){
        if (line.find(variable) != std::string::npos){
            size_t position = line.find('=');
            if (position != std::string::npos){
                std::string key = line.substr(0, position);
                value = line.substr(position + 1);
                return value;
            }
        }
    }

    return "it worked";
}
