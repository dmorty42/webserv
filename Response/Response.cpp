//
// Created by Darkside Morty on 4/7/22.
//

#include "Response.hpp"

Response::Response() { }

Response::~Response() { }

std::string getPageBody(Request& request) {
    return (request.getMethodCode().getPage());
}

void Response::prepareGetHeader(Request &request, Config &config) {
    int t = config.getHost().port;
    (void)t;
    int i = request.getMethodCode().getCode();
    switch (i) {
        case 200:
            _header = "HTTP/1.1 200 OK\r\n\r\n";
            _body = getPageBody(request);
    }
}

Response::Response(Request &request, Config& config) {
//    std::cout << "page address" << request.getMethodCode().getPagePath() << std::endl
//    << "code " << request.getMethodCode().getCode() << std::endl;
//    std::cout << request.getMethodCode().getPage() << std::endl;
    if (request.getMethodCode().getMethod() == GET)
        prepareGetHeader(request, config);
}

// Getters

std::string Response::getBody() const { return _body; }

std::string Response::getHeader() const { return _header; }