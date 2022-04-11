//
// Created by Darkside Morty on 4/3/22.
//

#include "Request.hpp"

Request::Request() {}

Request::~Request() {}


Request::Request(std::string& buff, Config* config) : _request(buff), _method(ft_method(buff)),
                                    _path(ft_path(buff)), _version(ft_version(buff)),
                                    _body(buff.substr(buff.find("\r\n\r\n"))){
    _values = ft_values(buff);
    _methodCode = new Methods(*this, *config);
    std::cout << _request;
}

// Getters

std::string Request::getRequest() const { return (_request); }

std::string Request::getMethod() const { return (_method); }

std::string Request::getPath() const { return (_path); }

std::string Request::getVersion() const { return (_version); }

std::map <std::string, std::string> Request::getValues() const { return (_values); }

std::string Request::getBody() const { return (_body); }

Methods Request::getMethodCode() const { return *_methodCode; }
