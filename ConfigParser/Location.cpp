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
    return (atol(block.substr(i[0], i[1] - i[0]).c_str()));
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

Location::Location(std::string block, std::string directory) {
    name = directory;
    root = parseRoot(block);
    allowedMethods = parseMethod(block);
    index = parseIndex(block);
    bodySize = parseBodySize(block) * MEGA;
    auto_index = parseAutoIndex(block);
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