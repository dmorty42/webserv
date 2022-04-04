//
// Created by Darkside Morty on 4/4/22.
//

#include "Methods.hpp"

Methods::Methods() {
    _code = 0;
    _method = UNDEFINED;
    _autoIndex = false;
    _allowedMethods[0] = "GET";
    _allowedMethods[1] = "POST";
    _allowedMethods[2] = "DELETE";
    fprt[0] = &Methods::methodGet;
    fprt[1] = &Methods::methodPost;
    fprt[2] = &Methods::methodDelete;
}

Methods::Methods(Request &request, Config& config) {
    _allowedMethods[0] = "GET";
    _allowedMethods[1] = "POST";
    _allowedMethods[2] = "DELETE";
    _code = 0;
    _method = UNDEFINED;
    _autoIndex = false;
    fprt[0] = &Methods::methodGet;
    fprt[1] = &Methods::methodPost;
    fprt[2] = &Methods::methodDelete;
    for (int i = 0; i < 3; ++i) {
        if (!request.getMethod().compare(_allowedMethods[i])) {
            (this->*fprt[i])(request, config);
            break;
        }
    }
}

std::map<std::string, std::string> splitBody(std::string body, std::string delim) {
    std::map<std::string, std::string> temp;
    std::string filename;
    size_t z[2];
    int i = body.find(delim);
    for (; i != (int)std::string::npos;) {
        z[0] = body.find("filename", i) + 10;
        z[1] = body.find("\"", z[0]);
        filename = body.substr(z[0], z[1] - z[0]);
        z[0] = body.find("Content-Type", i);
        z[0] = body.find("\n", z[0]) + 2;
        i = body.find(delim, i);
        temp[filename] = body.substr(z[0], i - z[0]);
    }
    return temp;
}

std::map<std::string, std::string> oneBody(Request& request) {
    std::map<std::string, std::string> temp;
    std::string fileName = request.getPath().substr(request.getPath().rfind("/") + 1,
                                                    request.getPath().size() -
                                                    request.getPath().rfind("/") - 1);
    temp[fileName] = request.getBody();
    return temp;
}

std::ofstream* creatingFile(std::string fileName, Location& location) {
    std::string path = location.getRoot().append("/");
    path.append(fileName);
    std::ofstream *ofs;
    for (int i = 1;  ; ++i) {
        if (!access(path.c_str(), 0))
            path.append(std::to_string(i));
        else {
            ofs = new std::ofstream(path);
            break;
        }
    }
    return (ofs);
}

void Methods::methodPost(Request &request, Config &config) {
    size_t i = 0;
    std::map<std::string, std::string> body;
    std::string delim;
    Location temp = search_location(request.getPath(), config.getLocation());
    for (; i < temp.getAllowedMethods().size(); ++i) {
        if (!temp.getAllowedMethods()[i].compare("POST"))
            break;
    }
    if (i == temp.getAllowedMethods().size()) {
        _code = 405;
        return;
    }
    _method = POST;
    int bodySize = stoi(request.getValues().find("Content-Length")->second);
    if (bodySize > temp.getBodySize()) {
        _code = 403;
        return;
    }
    if (request.getValues()["Content-Type"].find("multipart") != std::string::npos) {
        delim = request.getBody().substr(0, request.getBody().find("\n"));
        body = splitBody(request.getBody(), delim);
    } else
        body = oneBody(request);
    std::ofstream *ofs;
    std::map<std::string, std::string>::iterator it = body.begin();
    for (; it != body.end() ; ++it) {
        ofs = creatingFile(it->first, temp);
        *ofs << it->second;
    }
    ofs->close();
    _code = 200;
}

void Methods::methodGet(Request &request, Config& config) {
    size_t i = 0;
    Location temp = search_location(request.getPath(), config.getLocation());
    for (; i < temp.getAllowedMethods().size(); ++i) {
        if (!temp.getAllowedMethods()[i].compare("GET"))
            break;
    }
    if (i == temp.getAllowedMethods().size()) {
        _code = 405;
        return;
    }
    _method = GET;
    std::string fileName = temp.getRoot().append(request.getPath());
    if (fileName[fileName.size() - 1] == '/') {
        if (temp.getAutoIndex()) {
            _code = 200;
            _autoIndex = true;
            return;
        } else
            fileName.append(temp.getIndex());
    }
    if (!access(fileName.c_str(), 0)) {
        _pagePath = fileName;
        _code = 200;
        return;
    }
    _code = 404;
}

void Methods::methodDelete(Request &request, Config &config) {
    size_t i = 0;
    Location temp = search_location(request.getPath(), config.getLocation());
    for (; i < temp.getAllowedMethods().size(); ++i) {
        if (!temp.getAllowedMethods()[i].compare("GET"))
            break;
    }
    if (i == temp.getAllowedMethods().size()) {
        _code = 405;
        return;
    }
    _method = DELETE;
    std::string fileName = temp.getRoot().append(request.getPath());
    if (remove(fileName.c_str()))
        _code = 404;
    _code = 200;
}

// Getters
int Methods::getMethod() const { return _method; }

int Methods::getCode() const { return _code; }

bool Methods::getAutoIndex() const { return _autoIndex; }
