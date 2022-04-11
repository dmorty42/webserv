//
// Created by Darkside Morty on 3/25/22.
//

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "string"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <sys/event.h>
#include <sys/time.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "fstream"
#include <netinet/in.h>
#include <map>
#include <set>
#include <sstream>
#include "./ConfigParser/Config.hpp"
#include "./ConfigParser/ConfigParser.hpp"
#include "./ConfigParser/Location.hpp"
#include "./Cluster/Cluster.hpp"
#include "./Cluster/Server.hpp"
#include "./Request/Request.hpp"
#include "./Methods/Methods.hpp"
#include "./Response/Response.hpp"
#include "./AutoIndex/AutoIndex.hpp"

enum METHODS {
    GET = 0,
    POST = 1,
    DELETE = 2,
    UNDEFINED = 3
};

//Utils functions
void checkFileName(std::string fileName);
void putError();

//Server utils
int setWriteFlag(int& kq, int& sock);
int setReadFlag(int& kq, int& sock);
const Location &search_location(std::string path,
                                const std::map<std::string, Location> &locations);

#endif
