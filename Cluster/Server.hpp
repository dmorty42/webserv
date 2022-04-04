//
// Created by Darkside Morty on 3/25/22.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Webserv.hpp"

class Request;
class Config;

class Server {
private:
    int _socket;
    sockaddr_in _addr;
    Config* _config;
    std::map<int, std::string> _buff;
    std::map<int, Request> _requests;

public:
    Server();
    ~Server();
    int setup(int& kq, ConfigParser& config, int index);
    int getSocket() const;
    int receive(int connection);
    int send();

};

#endif
