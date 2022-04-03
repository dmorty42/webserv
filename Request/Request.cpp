//
// Created by Darkside Morty on 4/3/22.
//

#include "Request.hpp"

Request::Request() {}

Request::~Request() {}


Request::Request(std::string& buff) : _request(buff), _method(ft_method(buff)), _path(ft_path(buff)),
                                    _version(ft_version(buff)), _values(ft_values(buff)) {
}

// Getters

std::string Request::getRequest() const { return (_request); }

std::string Request::getMethod() const { return (_method); }

std::string Request::getPath() const { return (_path); }

std::string Request::getVersion() const { return (_version); }
