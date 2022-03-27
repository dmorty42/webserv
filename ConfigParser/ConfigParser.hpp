//
// Created by Darkside Morty on 24/03/2022.
//

#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include "../Webserv.hpp"

class Config;

class ConfigParser {
private:
    std::vector<Config> config;
public:
    ConfigParser();
    ConfigParser(std::string configFile);
    std::vector<Config> getConfig() const;
};


#endif
