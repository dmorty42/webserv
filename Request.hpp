//
// Created by Darkside Morty on 3/5/22.
//

#ifndef WEBSERV_REQUEST_HPP
#define WEBSERV_REQUEST_HPP

#include "string"
#include "iostream"

class Request {
private:
    std::string request;
    std::string method;
    std::string path;
    std::string version;
    std::string host;
public:
    Request(){}
    Request(const char *buff);
    void setMethod(const std::string &method);
    void setPath(const std::string &path);
    void setVersion(const std::string &ver);
    void setHost(const std::string &host);
    std::string getMethod() const;
    std::string getPath() const;
    std::string getVersion() const;
    std::string getHost() const;
};

std::ostream& operator<<(std::ostream &out, const Request& a);

#endif //WEBSERV_REQUEST_HPP
