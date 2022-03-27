//
// Created by Darkside Morty on 24/03/2022.
//

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(std::string configFile) {
    std::ifstream ifs(configFile);
    std::vector<bool> brackets;
    std::string temp, line;
    if (!ifs.is_open()) {
        perror("Error: can't open configuration file: ");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; std::getline(ifs, temp) ;) {
        if (temp.find("{") != std::string::npos) {
            brackets.push_back(false);
            i++;
        }
        if (temp.find("}") != std::string::npos) {
            brackets[i - 1] = true;
            i--;
        }
        line.append(temp);
        line.append("\n");
        if (brackets.size() != 0 && brackets[0] == true) {
           config.push_back(Config(line));
           line.clear();
           brackets.clear();
        }
    }
}

std::vector <Config> ConfigParser::getConfig() const {
    return (config);
}
