//
// Created by Darkside Morty on 4/7/22.
//

#include "Response.hpp"

Response::Response() { }

Response::~Response() { }

std::string getPageBody(Request& request, Config& config, int code) {
    std::string body;
    if (code == 200)
        return (request.getMethodCode().getPage());
    if (code == 404) {
        std::ifstream ifs;
        ifs.open(config.getPages()[404].c_str());
        for (std::string temp; !ifs.eof() ; temp.erase()) {
            std::getline(ifs, temp);
            body.append(temp + "\n");
        }
        ifs.close();
    }
    return (body);
}


void Response::prepareGetHeader(Request &request, Config &config) {
    int i = request.getMethodCode().getCode();
    switch (i) {
        case 200:
            _header = "HTTP/1.1 200 OK\r\n\r\n";
            _body = getPageBody(request, config, 200);
            break;
        case 404:
            _header = "HTTP/1.1 404 Not Found\r\n\r\n";
            _body = getPageBody(request, config, 404);
            break;
        case 405:
            _header = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
            _body = "Oopss... 405 Method Not Allowed!!!";
    }
}

void Response::preparePostHeader(Request &request, Config &config) {
    (void)config;
    int i = request.getMethodCode().getCode();
    switch (i) {
        case 200:
            _header = "HTTP/1.1 200 OK\r\n\r\n";
            _body = "It's OK! We got it!!!";
            break;
        case 403:
            _header = "HTTP/1.1 403 Forbidden\r\n\r\n";
            _body = "Oopss... 403 Forbidden!!!";
            break;
        case 405:
            _header = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
            _body = "Oopss... 405 Method Not Allowed!!!";
            break;
    }
}

void Response::prepareRedirectHeader(Request &request) {
    if (request.getMethodCode().getCode() == 301) {
        _header = "HTTP/1.1 301 Moved Permanently\r\nLocation: ";
    } else {
        _header = "HTTP/1.1 307 Temporary Redirect\r\nLocation: ";
    }
    _header.append(request.getMethodCode().getPagePath() + "\r\n\r\n");
    _body = "";
}

Response::Response(Request &request, Config& config) {
    if (request.getMethodCode().getCode() == 301 ||
        request.getMethodCode().getCode() == 307)
        prepareRedirectHeader(request);
    else if (!request.getMethodCode().getMethod().compare("GET"))
        prepareGetHeader(request, config);
    else if (!request.getMethodCode().getMethod().compare("POST"))
        preparePostHeader(request, config);
}

// Getters

std::string Response::getBody() const { return _body; }

std::string Response::getHeader() const { return _header; }

std::string Response::getResponse() {
    std::string temp(_header + _body);
    return (temp);
}