//
// Created by Darkside Morty on 4/3/22.
//

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../Webserv.hpp"

class Request {
private:
    std::string _request;
    std::string _method;
    std::string _path;
    std::string _version;
    std::map<std::string, std::string> _values;
public:
    Request();
    Request(std::string& buff);
    ~Request();
    std::string getRequest() const;
    std::string getMethod() const;
    std::string getPath() const;
    std::string getVersion() const;
};

std::string ft_method(std::string& buff);
std::string ft_path(std::string& buff);
std::string ft_version(std::string& buff);
std::map<std::string, std::string> ft_values(std::string& buff);

#endif