//
// Created by Darkside Morty on 24/03/2022.
//

#pragma once

#include "../Webserv.hpp"
#include "Config.hpp"
#define MEGA 1048576

class Config;

typedef struct s_redirect {
    int code;
    std::string target;
} t_redirect;

class Location {
private:
    std::string name;
    std::string root;
    std::vector<std::string> allowedMethods;
    std::string index;
    t_redirect redirect;
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
    t_redirect getRedirect() const;
};

std::string parseIndex(std::string block);
