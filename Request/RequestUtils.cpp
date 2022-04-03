//
// Created by Darkside Morty on 4/3/22.
//

#include "Request.hpp"

std::string ft_method(std::string& buff) {
    return (buff.substr(0, buff.find(" ")));
}

std::string ft_path(std::string& buff) {
    size_t i[2];
    i[0] = buff.find(" ") + 1;
    i[1] = buff.find(" ", i[0]);
    return (buff.substr(i[0], i[1] - i[0]));
}

std::string ft_version(std::string& buff) {
    size_t i[2];
    i[0] = buff.find("HTTP/");
    i[1] = buff.find("\n", i[0]);
    return (buff.substr(i[0], i[1] - i[0]));
}

std::map<std::string, std::string> ft_values(std::string& buff) {
    std::map<std::string, std::string> temp;
    std::string key, value;
    size_t i[2];
    i[0] = buff.find("\n");
    for (; i[0] != std::string::npos; ) {
        i[1] = buff.find(":", i[0]);
        if (i[1] == std::string::npos)
            break;
        key = buff.substr(i[0] + 1, i[1] - i[0] - 1);
        i[0] = buff.find("\n", i[1]);
        if (i[0] == std::string::npos)
            i[0] = buff.find("\0");
        value = buff.substr(i[1] + 2, i[0] - i[1] -1);
        temp[key] = value;
        i[0] = buff.find("\n", i[1]);
        key.erase();
        value.erase();
    }
    return (temp);
}
