//
// Created by Darkside Morty on 3/7/22.
//

#ifndef WEBSERV_PAGE_HPP
#define WEBSERV_PAGE_HPP

#include "string"
#include "fstream"
#include "iostream"
#include "unistd.h"
#include "cstdlib"

class Page {
private:
    std::string content;
    size_t len;
public:
    Page(const char* pageDirection);
    std::string getContent() const;
    size_t getLen() const;
    void sendPage(int socket) const;
};


#endif //WEBSERV_PAGE_HPP
