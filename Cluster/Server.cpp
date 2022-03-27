//
// Created by Darkside Morty on 3/25/22.
//

#include "Server.hpp"

Server::Server() {
}

int Server::setup(int& kq, ConfigParser& config, int index) {
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(config.getConfig()[index].getHost().port);
    _addr.sin_addr.s_addr = htonl(config.getConfig()[index].getHost().host);
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error: socket: ");
        return (EXIT_FAILURE);
    }
    int i = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) < 0) {
        perror("Error: setsockopt: ");
        return (EXIT_FAILURE);
    }
    if (bind(_socket, (sockaddr *)&_addr, sizeof(_addr)) != 0) {
        perror("Error: bind: ");
        close(_socket);
        return (EXIT_FAILURE);
    }
    if (listen(_socket, SOMAXCONN) != 0) {
        perror("Error: listen: ");
        close(_socket);
        return (EXIT_FAILURE);
    }
    if (setReadFlag(kq, _socket)) {
        perror("Error: flag setting: ");
        close(_socket);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int Server::getSocket() const {return (_socket);}
