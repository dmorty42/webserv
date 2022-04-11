//
// Created by Darkside Morty on 4/8/22.
//

#ifndef AUTOINDEX_HPP
#define AUTOINDEX_HPP

#include "../Webserv.hpp"

class AutoIndex {
private:
    static std::string getLink(const std::string& dirEntry, const std::string& dirName,
                       const std::string& host, const int port);
public:
    AutoIndex();
    ~AutoIndex();
    static std::string getPage(const std::string& path, const std::string& host, const int port);

};


#endif
