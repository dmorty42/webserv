//
// Created by Darkside Morty on 3/25/22.
//

#include "Server.hpp"

Server::Server() {
}

Server::~Server() {}

int Server::setup(int& kq, ConfigParser& config, int index) {
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(config.getConfig()[index].getHost().port);
    _addr.sin_addr.s_addr = htonl(config.getConfig()[index].getHost().host);
    _config =  new Config(config.getConfig()[index]);
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

int Server::receive(int connection) {
    char buff[MEGA];
    size_t header, length, body;
    size_t ret = ::recv(connection, buff, MEGA, 0);
    // std::cout << "!\n" << buff << "!\n" << std::endl;
    if (ret < 1) {
        close(connection);
        if (ret < 0)
            perror("Receive: ");
        else {
            _buff.erase(connection);
            std::cout << "Client closed connection!" << std::endl;
        }
        return (EXIT_FAILURE);
    }
    _buff[connection].append(buff, ret);
    if ((header = _buff[connection].find("\r\n\r\n")) != std::string::npos) {
        if (( body =_buff[connection].find("Content-Length")) != std::string::npos) {
            body = std::stoi(_buff[connection].substr(body + 16));
            length = _buff[connection].size();
            if (length < body + header + 4)
                return 1;
        }
        _requests[connection] = Request(_buff[connection], _config, connection);
        _buff.erase(connection);
        return (0);
    }
    return (1);
}

int Server::send(int connection) {
    _response[connection] = Response(_requests[connection], *_config);
    ::send(connection, _response[connection].getResponse().c_str(),
           _response[connection].getResponse().size(), 0);
    _requests.erase(connection);
    _response.erase(connection);
    return (1);
}

