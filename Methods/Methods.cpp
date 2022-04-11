//
// Created by Darkside Morty on 4/4/22.
//

#include "Methods.hpp"

Methods::Methods() {
    _code = 0;
    _method = "";
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
    _method = request.getMethod();
    _autoIndex = false;
    fprt[0] = &Methods::methodGet;
    fprt[1] = &Methods::methodPost;
    fprt[2] = &Methods::methodDelete;
    Location location = search_location(request.getPath(),
                                        config.getLocation());
    if (location.getRedirect().code != 0) {
        methodRedirect(request, location);
    } else {
        for (int i = 0; i < 3; ++i) {
            if (!request.getMethod().compare(_allowedMethods[i])) {
                (this->*fprt[i])(request, config, location);
                break;
            }
        }
    }
}

Methods::~Methods() { }

void Methods::methodRedirect(Request &request, Location &location) {
    if  (std::find(location.getAllowedMethods().begin(), location.getAllowedMethods().end(),
              request.getMethod()) == location.getAllowedMethods().end()) {
        _code = 403;
        return;
    }
    _code = location.getRedirect().code;
    _pagePath = location.getRedirect().target;
}



void Methods::methodPost(Request &request, Config &config, Location& location) {
    size_t i = 0;
    (void)config;
    std::map<std::string, std::string> body;
    std::string delim;
    for (; i < location.getAllowedMethods().size(); ++i) {
        if (!location.getAllowedMethods()[i].compare("POST"))
            break;
    }
    if (i == location.getAllowedMethods().size()) {
        _code = 405;
        return;
    }
    long bodySize = stol(request.getValues().find("Content-Length")->second);
    if (bodySize > location.getBodySize()) {
        _code = 403;
        return;
    }
    if (request.getValues()["Content-Type"].find("multipart") != std::string::npos) {
        delim = request.getValues()["Content-Type"].substr(
                request.getValues()["Content-Type"].find("boundary") + 9);
        body = splitBody(request.getBody(), delim);
    } else {
        body = oneBody(request);
    }
    std::map<std::string, std::string>::iterator it = body.begin();
    for (; it != body.end() ; ++it) {
        creatingFile(it->first, location, it->second);
    }
    _code = 200;
}

void Methods::getPageContent(std::string &fileName) {
    std::string temp;
    std::ifstream ifs;
    ifs.open(fileName.c_str());
    if (!ifs.is_open()) {
        std::cerr << "Error: can't open file: " << fileName << std::endl;
        _code = 404;
        return;
    }
    for (; !ifs.eof() ; ) {
        std::getline(ifs, temp);
        _page.append(temp);
        _page.append("\n");
    }
    ifs.close();
}

void Methods::methodGet(Request &request, Config& config, Location& location) {
    size_t i[2];
    i[0] = 0;
    for (; i[0] < location.getAllowedMethods().size(); ++i[0]) {
        if (!location.getAllowedMethods()[i[0]].compare("GET"))
            break;
    }
    if (i[0] == location.getAllowedMethods().size()) {
        _code = 405;
        return;
    }
    std::string fileName = location.getRoot().append(request.getPath());
    i[0] = fileName.find(location.getName());
    i[1] = location.getName().size();
    fileName.replace(i[0], i[1], "");
    if (fileName[fileName.size() - 1] == '/') {
        if (location.getAutoIndex()) {
            _pagePath = fileName;
            _page = AutoIndex::getPage(_pagePath, config.getStrHost(), config.getHost().port);
            _code = 200;
            _autoIndex = true;
            return;
        } else
            fileName.append(location.getIndex());
    }
    DIR *dir = opendir(fileName.c_str());
    _pagePath = fileName;
    if (dir) {
        closedir(dir);
        _code = 404;
        return;
    }
    if (!access(fileName.c_str(), 0)) {
        getPageContent(fileName);
        _code = 200;
        return;
    }
    _code = 404;
}

void Methods::methodDelete(Request &request, Config &config, Location& location) {
    size_t i = 0;
    (void)config;
    for (; i < location.getAllowedMethods().size(); ++i) {
        if (!location.getAllowedMethods()[i].compare("GET"))
            break;
    }
    if (i == location.getAllowedMethods().size()) {
        _code = 405;
        return;
    }
    std::string fileName = location.getRoot().append(request.getPath());
    if (remove(fileName.c_str()))
        _code = 404;
    _code = 200;
}

// Getters
std::string Methods::getMethod() const { return _method; }

int Methods::getCode() const { return _code; }

bool Methods::getAutoIndex() const { return _autoIndex; }

std::string Methods::getPagePath() const { return _pagePath; }

std::string Methods::getPage() const { return _page; }
