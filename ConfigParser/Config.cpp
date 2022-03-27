//
// Created by Darkside Morty on 22/03/2022.
//

#include "Config.hpp"

std::string parseServerName(std::string configFile) {
    size_t i[2];
    if ((i[0] = configFile.find("server_name")) != std::string::npos) {
        i[1] = configFile.find("\n", i[0]);
        return (configFile.substr(i[0] + 12, i[1] - i[0] - 12));
    }
    return ("default_server");
}

t_host parseHost(std::string configFile) {
    t_host host;
    size_t i[2];
    std::string temp;
    if (configFile.find("listen") != std::string::npos) {
       temp = configFile.substr(configFile.find("listen"));
        i[0] = temp.find(":");
        host.port = atoi(temp.substr(i[0] + 1).c_str());
        i[1] = temp.find("listen") + 7;
        temp = temp.substr(i[1], i[0] - i[1]);
        host.host = inet_addr(temp.c_str());
        }
    return (host);
}

std::string parseRoot(std::string configFile) {
        size_t i[2];
        if ((i[0] = configFile.find("root")) != std::string::npos) {
            i[1] = configFile.find("\n", i[0]);
            return (configFile.substr(i[0], i[1] - i[0]));
        }
    return ("none");
}

std::vector<std::string> parseMethod(std::string configFile) {
    size_t i[2];
    std::string temp;
    i[0] = configFile.find("allow_methods") + 14;
    i[1] = configFile.find("\n", i[0]);
    temp = configFile.substr(i[0], i[1] - i[0]);
    std::vector<std::string> meth;
    for (i[0] = 0; i[0] != std::string::npos;) {
        i[1] = temp.find(" ", i[0]);
        if (i[1] != std::string::npos) {
            meth.push_back(temp.substr(i[0], i[1] - i[0]));
            i[0] = i[1] + 1;
        }
        else {
            meth.push_back(temp.substr(i[0]));
            break;
        }
    }
    return meth;
}

std::string parseBlock(std::string configFile, size_t pos) {
    size_t i[2];
    i[0] = configFile.find("{", pos);
    i[1] = configFile.find("}", i[0]);
    return (configFile.substr(i[0], i[1] - i[0] + 1));
}

std::map<std::string, Location> parseLocation(std::string configFile) {
    size_t i[2];
    std::string directory, block;
    std::map<std::string, Location> temp;
    Location a;
    i[0] = configFile.find("location");
    for (; i[0] != std::string::npos; ) {
        i[1] = configFile.find("{", i[0]) - 1;
        directory = configFile.substr(i[0] + 9, i[1] - i[0] - 9);
        std::cout << directory << std::endl;
        block = parseBlock(configFile, i[0]);
        temp[directory] = Location(block);
        std::cout << block << std::endl;
        i[0] = configFile.find("location", i[0] + 9);
    }
    return (temp);
}

Config::Config(std::string configFile) {
    serverName = parseServerName(configFile);
    host = parseHost(configFile);
    root = parseRoot(configFile);
    allowedMethods = parseMethod(configFile);
    location = parseLocation(configFile);
}

// Getters

std::string Config::getServerName() const {
    return (serverName);
}

t_host Config::getHost() const {
    return (host);
}

std::string Config::getRoot() const {
    return (root);
}

std::vector <std::string> Config::getAllowedMethods() const {
    return (allowedMethods);
}

std::map <std::string, Location> Config::getLocation() const {
    return (location);
}
