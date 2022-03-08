//
// Created by Darkside Morty on 3/5/22.
//

#include "Request.hpp"

Request::Request(const char *buff) : request(buff){
    size_t i = request.find(' ');
    setMethod(request.substr(0, i));
    setPath(request.substr(i + 1, request.find(' ', i + 1) - i - 1));
    i = request.find(' ', i + 1);
    setVersion(request.substr(i, request.find('\n') - 1 - i));
    i = request.find("Host") + 6;
    size_t a = request.find('\n', i);
    setHost(request.substr(i, a - i - 1));
}

void Request::setMethod(const std::string &method) {
    this->method = method;
}

void Request::setPath(const std::string &path) {
    this->path = path;
}

void Request::setVersion(const std::string &ver) {
    this->version = ver;
}

void Request::setHost(const std::string &host) {
    this->host = host;
}

std::string Request::getMethod() const {
    return (this->method);
}

std::string Request::getPath() const {
    return (this->path);
}

std::string Request::getVersion() const {
    return (this->version);
}

std::string Request::getHost() const {
    return (this->host);
}


std::ostream& operator<<(std::ostream &out, const Request& a) {
    out << "Method: " << a.getMethod() << "! Path: " << a.getPath()
        << "! Version: " << a.getVersion() << "! Host: " << a.getHost()
        << "!" << std::endl;
    return (out);
}