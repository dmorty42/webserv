//
// Created by Darkside Morty on 4/12/22.
//

#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include "../Webserv.hpp"

class CgiHandler {
private:
    std::map<std::string, std::string> _env;
    void prepareEnv(Request& request, Config& config);
    char **mapEnvToArray();
    void handleCgi();
public:
    CgiHandler();
    CgiHandler(const CgiHandler& other);
    CgiHandler& operator=(const CgiHandler& other);
    ~CgiHandler();
    CgiHandler(Request& request, Config& config);
};


#endif
