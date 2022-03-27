
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../Webserv.hpp"

class Location;

typedef struct s_host {
    u_int32_t host;
    int port;
} t_host;

class Config {
private:
    std::string serverName;
    t_host host;
    std::string root;
    std::vector<std::string> allowedMethods;
    std::map<std::string, Location> location;
public:
    Config(std::string configFile);
    std::string getServerName() const;
    t_host getHost() const;
    std::string getRoot() const;
    std::vector<std::string> getAllowedMethods() const;
    std::map<std::string, Location> getLocation() const;
};

std::string parseServerName(std::string configFile);
t_host parseHost(std::string configFile);
std::string parseRoot(std::string configFile);
std::vector<std::string> parseMethod(std::string configFile);

#endif
