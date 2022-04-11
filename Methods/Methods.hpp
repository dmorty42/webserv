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
    std::string _method;
    bool _autoIndex;
    std::string _page;
    std::string _pagePath;
    std::string _allowedMethods[3];

    void (Methods::*fprt[3])(Request& request, Config& config, Location& location);
    void methodGet(Request& request, Config& config, Location& location);
    void methodPost(Request& request, Config& config, Location& location);
    void methodDelete(Request& request, Config& config, Location& location);
    void getPageContent(std::string& fileName);
    void methodRedirect(Request& request ,Location& location);

public:
    Methods();
    Methods(Request& request, Config& config);
    ~Methods();
    int getCode() const;
    std::string getMethod() const;
    bool getAutoIndex() const;
    std::string getPagePath() const;
    std::string getPage() const;
};

std::map<std::string, std::string> splitBody(const std::string& body, const std::string& delim);
std::map<std::string, std::string> oneBody(Request& request);
void creatingFile(std::string fileName, Location& location,
                  std::string& content);

#endif
