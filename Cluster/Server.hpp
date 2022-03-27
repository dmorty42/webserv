//
// Created by Darkside Morty on 3/25/22.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Webserv.hpp"

class ConfigParser;

class Server {
private:
    int _socket;
    sockaddr_in _addr;
public:
    Server();
    int setup(int& kq, ConfigParser& config, int index);
    int getSocket() const;

};

#endif