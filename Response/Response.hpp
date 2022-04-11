//
// Created by Darkside Morty on 4/7/22.
//

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../Webserv.hpp"

class Request;
class Config;

class Response {
private:
    std::string _header;
    std::string _body;

    void prepareGetHeader(Request& request, Config& config);
    void preparePostHeader(Request& request, Config& config);
    void prepareRedirectHeader(Request& request);
public:
    Response();
    Response(Request& request, Config& config);
    ~Response();

    std::string getHeader() const;
    std::string getBody() const;
    std::string getResponse();

};


#endif
