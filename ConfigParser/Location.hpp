//
// Created by Darkside Morty on 24/03/2022.
//

#pragma once

#include "../Webserv.hpp"
#include "Config.hpp"
#define MEGA 1048576

class Config;

class Location {
private:
    std::string name;
    std::string root;
    std::vector<std::string> allowedMethods;
    std::string index;
    bool auto_index;
    long bodySize;
public:
    Location() {};
    Location(std::string block, std::string directory);

    std::string getRoot() const;
    std::vector<std::string> getAllowedMethods() const;
    std::string getIndex() const;
    long getBodySize() const;
    std::string getName() const;
    bool getAutoIndex() const;
};

std::string parseIndex(std::string block);
