//
// Created by Darkside Morty on 3/25/22.
//

#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "../Webserv.hpp"

class Server;
class ConfigParser;

class Cluster {
private:
    char **_env;
    int _kq;
    ConfigParser* _config;
    std::map<int, Server> _listener;
    std::map<int, Server> _connection;
public:
    Cluster();
    Cluster(char **env);
    virtual ~Cluster();
    int setup(const std::string& fileName);
    int run();
};

typedef std::map<int, Server>::iterator ServerIterator;

#endif

