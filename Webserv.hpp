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
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "fstream"
#include <netinet/in.h>
#include <map>
#include "./ConfigParser/Config.hpp"
#include "./ConfigParser/ConfigParser.hpp"
#include "./ConfigParser/Location.hpp"
#include "./Cluster/Cluster.hpp"
#include "./Cluster/Server.hpp"

//Utils functions
void checkFileName(std::string fileName);
void putError();

//Server utils
int setWriteFlag(int& kq, int& sock);
int setReadFlag(int& kq, int& sock);

#endif
