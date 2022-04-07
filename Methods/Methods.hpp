//
// Created by Darkside Morty on 4/4/22.
//

#ifndef METHODS_HPP
#define METHODS_HPP

#include "../Webserv.hpp"

class Request;


class Methods {
private:
    int _code;
    int _method;
    bool _autoIndex;
    std::string _page;
    std::string _pagePath;
    std::string _allowedMethods[3];

    void (Methods::*fprt[3])(Request& request, Config& config);
    void methodGet(Request& request, Config& config);
    void methodPost(Request& request, Config& config);
    void methodDelete(Request& request, Config& config);
    void getPageContent(std::string& fileName);

public:
    Methods();
    Methods(Request& request, Config& config);
    ~Methods();
    int getCode() const;
    int getMethod() const;
    bool getAutoIndex() const;
    std::string getPagePath() const;
    std::string getPage() const;
};


#endif
