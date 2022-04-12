
#pragma once

#include "../Webserv.hpp"
#include "Location.hpp"

class Location;

typedef struct s_host {
    u_int32_t host;
    int port;
} t_host;

class Config {
private:
    std::string serverName;
    t_host host;
    std::string strHost;
    char **_env;
    std::map<int, std::string> pages;
    std::vector<std::string> allowedMethods;
    std::map<std::string, Location> location;

    t_host parseHost(std::string configFile);
public:
    Config();
    Config(std::string configFile, char** env);
    Config(const Config& other);
    Config& operator=(const Config& other);
    std::string getServerName() const;
    t_host getHost() const;
    std::string getStrHost() const;
    std::vector<std::string> getAllowedMethods() const;
    std::map<std::string, Location> getLocation() const;
    std::map<int, std::string> getPages() const;
    char **getEnv() const;
};

std::string parseServerName(std::string configFile);
std::string parseRoot(std::string configFile);
std::vector<std::string> parseMethod(std::string configFile);

