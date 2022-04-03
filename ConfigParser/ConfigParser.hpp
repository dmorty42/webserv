//
// Created by Darkside Morty on 24/03/2022.
//

#pragma once

#include "../Webserv.hpp"
#include "Config.hpp"

class Config;

class ConfigParser {
private:
    std::vector<Config> config;
public:
    ConfigParser(std::string configFile);
    std::vector<Config> getConfig() const;
};

