//
// Created by Darkside Morty on 4/12/22.
//

#include "CgiHandler.hpp"

CgiHandler::CgiHandler() {}

CgiHandler::CgiHandler(const CgiHandler &other) {
    if (this != &other) {
        this->_env = other._env;
    }
}

CgiHandler &CgiHandler::operator=(const CgiHandler &other) {
    if (this != &other) {
        this->_env = other._env;
    }
    return (*this);
}

CgiHandler::~CgiHandler() {}

CgiHandler::CgiHandler(Request &request, Config &config) {
    prepareEnv(request, config);
    handleCgi();
}

void CgiHandler::prepareEnv(Request& request, Config& config) {
    std::map<std::string, std::string> header = request.getValues();
    std::map<std::string, std::string>::iterator ite = header.end();
    Location location = search_location(request.getPath(), config.getLocation());
    if (header.find("Auth-Scheme") != ite)
        _env["AUTH-TYPE"] = header["Authorization"];
    if (header.find("Content-Length") != ite)
        _env["CONTENT_LENGTH"] = header["Content-Length"];
    if (header.find("Content-Type") != ite)
        _env["CONTENT-TYPE"] = header["Content-Type"];
    _env["GATEWAY_INTERFACE"] = "CGI/1.1";
    _env["PATH_INFO"] = request.getPath();
    _env["PATH_TRANSLATED"] = request.getPath();
    _env["QUERY_STRING"] = request.getQuery();
    _env["REMOTE_ADDR"] = config.getStrHost();
    _env["REMOTE_HOST"] = config.getStrHost();
    if (header.find("Autorization") != ite) {
        _env["REMOTE_IDENT"] = header["Authorization"];
        _env["REMOTE_USER"] = header["Autorization"].substr(
                header["Autorization"].find('.') + 1);
    }
    _env["REQUEST_METHOD"] = request.getMethod();
    _env["SCRIPT_NAME"] = location.getRoot() + request.getPath().substr(1);
    _env["SERVER_NAME"] = config.getServerName();
    _env["SERVER_PORT"] = IntToStr(config.getHost().port);
    _env["SERVER_PROTOCOL"] = "HTTP/1.1";
    _env["SERVER_SOFTWARE"] = "webserv/1.1";
}

char **CgiHandler::mapEnvToArray() {
    char **temp = new char*[_env.size() + 1];
    int i = 0;
    for (std::map<std::string, std::string>::iterator it = _env.begin();
                    it != _env.end() ; it++) {
        std::string str(it->first + "=" + it->second);
        temp[i] = new char[str.size() + 1];
        temp[i] = strdup(str.c_str());
        i++;
    }
    temp[i] = NULL;
    return temp;
}

void CgiHandler::handleCgi() {
    pid_t pid;
    int i = 0;

    pid = fork();
    if (pid < 0) {
        std::cerr << "Fork crashed...";
        return;
    }
    if (!pid) {
        std::string fileName = _env["SCRIPT_NAME"];
        char *temp[3];
        temp[0] = strdup("/usr/local/bin/python3");
        temp[1] = strdup(fileName.c_str());
        temp[2] = NULL;
        execve(temp[0], temp, mapEnvToArray());
        std::cerr << "Execve crashed...";
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        waitpid(pid, &i, 0);
    }
}