//
// Created by Darkside Morty on 24/03/2022.
//

#include "Location.hpp"


std::string parseIndex(std::string block) {
    size_t i[2];
    i[0] = block.find("index");
    if (i[0] == block.find("auto_index") + 5)
        i[0] = block.find("index", i[0] + 1);
    if (i[0] == std::string::npos)
        return ("");
    i[0] += 6;
    i[1] = block.find("\n", i[0]);
    return (block.substr(i[0], i[1] - i[0]));
}

long parseBodySize(std::string block) {
    size_t i[2];
    i[0] = block.find("client_body_buffer_size");
    if (i[0] == std::string::npos)
        return (-1);
    i[0] += 24;
    i[1] = block.find("\n", i[0]);
    return (std::stol(block.substr(i[0], i[1] - i[0])));
}

bool parseAutoIndex(std::string block) {
    std::string temp;
    int i[2];
    i[0] = block.find("auto_index") + 11;
    i[1] = block.find("\n", i[0]);
    temp = block.substr(i[0], i[1] - i[0]);
    if (!temp.compare("on"))
        return true;
    return false;
}

t_redirect parseRedirect(std::string& block) {
    t_redirect temp;
    size_t i[2];
    i[0] = block.find("return");
    if (i[0] == std::string::npos) {
        temp.code = 0;
        return (temp);
    }
    i[1] = block.find(" ", i[0] + 7);
    temp.code = stoi(block.substr(i[0] + 7, i[1] - i[0] - 7));
    i[0] = block.find("\n", i[1] + 1);
    temp.target = block.substr(i[1] + 1, i[0] - i[1] - 1);
    return temp;
}

Location::Location(std::string block, std::string directory) {
    name = directory;
    root = parseRoot(block);
    allowedMethods = parseMethod(block);
    index = parseIndex(block);
    bodySize = parseBodySize(block) * MEGA;
    auto_index = parseAutoIndex(block);
    redirect = parseRedirect(block);
}


// Getters

std::string Location::getRoot() const {
    return (root);
}

std::vector <std::string> Location::getAllowedMethods() const {
    return (allowedMethods);
}

std::string Location::getIndex() const {
    return (index);
}

long Location::getBodySize() const {
    return (bodySize);
}

std::string Location::getName() const {
    return (name);
}

bool Location::getAutoIndex() const { return (auto_index); }

t_redirect Location::getRedirect() const { return redirect; }