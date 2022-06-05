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
    std::string key, value, str;
    size_t i[4];
    i[0] = buff.find("\n");
    i[2] = buff.find("\r\n\r\n");
    for (; i[0] != i[2] ; ) {
        i[1] = buff.find("\n", i[0] + 1);
        str = buff.substr(i[0] + 1, i[1] - i[0] - 2);
        i[3] = str.find(":");
        if (i[3] < 0 || i[3] >= buff.length())
            break;
        key = str.substr(0, i[3]);
        if (buff.find("POST") != std::string::npos)
            value = str.substr(i[3] + 2);
        temp[key] = value;
        i[0] = buff.find("\n", i[0] + 1);
        if (i[0] == std::string::npos || !key.compare("Cookie"))
            break;
    }
    return (temp);
}
