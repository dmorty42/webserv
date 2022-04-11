//
// Created by Darkside Morty on 4/8/22.
//


#include "AutoIndex.hpp"

std::string AutoIndex::getLink(const std::string &dirEntry, const std::string &dirName,
                               const std::string &host, const int port) {
    std::stringstream ss;
    ss << "\t\t<p><a href=\"http://" + host + ":" <<\
        port << dirName + "/" + dirEntry + "\">" + dirEntry + "</a></p>\n";
    return ss.str();
}

AutoIndex::AutoIndex() {}

AutoIndex::~AutoIndex() {}

std::string AutoIndex::getPage(const std::string &path, const std::string &host, const int port) {
    DIR *dir = opendir(path.c_str());
    std::string temp;
    std::string page = \
    "<!DOCTYPE html>\n\
    <html>\n\
    <head>\n\
            <title>" + path + "</title>\n\
    </head>\n\
    <body>\n\
    <h1>INDEX</h1>\n\
    <p>\n";
    if (dir == NULL) {
        std::cerr << "Error: can't open direction " << path << std::endl;
        return "";
    }
    for (struct dirent *dirEntry = readdir(dir); dirEntry ; dirEntry = readdir(dir)) {
        temp = dirEntry->d_name;
        page += getLink(temp, path, host, port);
    }
    page += "\
    </p>\n\
    </body>\n\
    </html>\n";
    closedir(dir);
    return page;
}